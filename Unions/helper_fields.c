#include "helper_fields.h"
#include <stdio.h>

static void dump_raw(const packet_header_t *pkt) {
  printf("raw:  ");
  for (size_t i = 0; i < sizeof(pkt->raw); i++) {
    printf("%02X ", pkt->raw[i]);
  }
  printf("\n");
}

int main(void) {
  printf("sizeof(tcp_header_t)   = %zu\n", sizeof(tcp_header_t));
  printf("sizeof(packet_header_t) = %zu\n", sizeof(packet_header_t));

  // Write through the typed view, read back through raw[].
  printf("--- write via tcp_header view ---\n");
  packet_header_t pkt = {
    .tcp_header = {
      .src_port = 8080,        // 0x1F90
      .dest_port = 80,         // 0x0050
      .seq_num = 0xDEADBEEFu,
    },
  };
  printf("src_port:  %u (0x%04X)\n", pkt.tcp_header.src_port, pkt.tcp_header.src_port);
  printf("dest_port: %u (0x%04X)\n", pkt.tcp_header.dest_port, pkt.tcp_header.dest_port);
  printf("seq_num:   %u (0x%08X)\n", pkt.tcp_header.seq_num, pkt.tcp_header.seq_num);
  dump_raw(&pkt);

  // Write through raw[], read back through the typed view.
  printf("--- write via raw[] view ---\n");
  packet_header_t raw_pkt;
  const uint8_t bytes[8] = {
    0x90, 0x1F,        // src_port  (little-endian 0x1F90 = 8080)
    0x50, 0x00,        // dest_port (little-endian 0x0050 = 80)
    0xEF, 0xBE, 0xAD, 0xDE, // seq_num (little-endian 0xDEADBEEF)
  };
  for (size_t i = 0; i < sizeof(raw_pkt.raw); i++) {
    raw_pkt.raw[i] = bytes[i];
  }
  printf("src_port:  %u (0x%04X)\n", raw_pkt.tcp_header.src_port, raw_pkt.tcp_header.src_port);
  printf("dest_port: %u (0x%04X)\n", raw_pkt.tcp_header.dest_port, raw_pkt.tcp_header.dest_port);
  printf("seq_num:   %u (0x%08X)\n", raw_pkt.tcp_header.seq_num, raw_pkt.tcp_header.seq_num);
  dump_raw(&raw_pkt);

  return 0;
}
