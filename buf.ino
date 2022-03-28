uint8_t buf[16];
uint8_t buf_head = 0;
uint8_t buf_tail = 0;

void buffAdd(uint8_t c) {
  buf[buf_tail++ % sizeof(buf)] = c;
  if (buf_tail % sizeof(buf) == buf_head % sizeof(buf)) {
    buf_head++;
  }
}

void buffToWire() {
  while (buf_tail % sizeof(buf) != buf_head % sizeof(buf)) {
    Wire_write(buf[buf_head++ % sizeof(buf)]);
  }
}
