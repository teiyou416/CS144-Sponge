#include "wrapping_integers.hh"

// Dummy implementation of a 32-bit wrapping integer

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) {
      return operator+(isn,n);    
}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    auto low32bit = static_cast<uint32_t>(n - isn);
    auto high32bit1 = (checkpoint + (1 << 31)) & 0xFFFFFFFF00000000;
    auto high32bit2 = (checkpoint - (1 << 31)) & 0xFFFFFFFF00000000;
    auto res1 = low32bit | high32bit1, res2 = low32bit | high32bit2;
    if (max(res1, checkpoint) - min(res1, checkpoint) < max(res2, checkpoint) - min(res2, checkpoint)) 
        return res1;
    return res2;
   }
    
