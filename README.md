## Padding

Chương trình sử dụng **Zero Padding** để xử lý dữ liệu không đủ block 8 bytes.

- Block size: 8 bytes (DES)
- Nếu dữ liệu không chia hết cho 8, sẽ thêm byte `0x00` vào cuối
- Khi giải mã, các byte `0x00` sẽ được loại bỏ

---

This program USES padding.

Padding scheme: ZERO PADDING.

Input data is padded with 0x00 bytes to make its length a multiple of 8 bytes.
