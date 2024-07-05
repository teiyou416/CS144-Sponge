#include "tcp_receiver.hh"
#include "stream_reassembler.hh"
#include "wrapping_integers.hh"
#include <optional>
// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
   const TCPHeader &header = seg.header();  
   if(!_set_syn_flag){
      if(!header.syn) {return;}
   _isn = header.seqno;
   _set_syn_flag = true;
    } 
  uint64_t abs_ackno = _reassembler.stream_out().bytes_written() + 1;
  uint64_t abs_seq = unwrap(header.seqno,_isn,abs_ackno);
  uint64_t stream_index = abs_seq - 1 + (header.syn);   
  _reassembler.push_substring(seg.payload().copy(),stream_index,header.fin);
   }

optional<WrappingInt32> TCPReceiver::ackno() const { 
    if (!_set_syn_flag)
        return nullopt;
    size_t abs_ack_no = _reassembler.stream_out().bytes_written() + 1;
    if (_reassembler.stream_out().input_ended()) {return wrap(abs_ack_no+1, _isn);}
    else return wrap(abs_ack_no, _isn);
}

size_t TCPReceiver::window_size() const { return _capacity - _reassembler.stream_out().buffer_size(); }
