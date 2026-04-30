# Báo cáo Lab 4 - DES & TripleDES

## Mục tiêu / Objective
Triển khai DES và TripleDES với multi-block, zero padding, hỗ trợ nhập từ bàn phím và các test negative.

## Cách làm / Approach
- Sử dụng bảng IP, FP, E, S-box, P, PC1, PC2 chuẩn.
- Key schedule sinh 16 round keys.
- Feistel function với S-box.
- Mode 1: DES Encrypt multi-block + Zero Padding.
- Mode 3 & 4: TripleDES EDE (Encrypt-Decrypt-Encrypt).
- In output dưới dạng chuỗi nhị phân.

## Kết quả / Result
- Q2 (Multi-block + padding): PASS
- Q4 (TripleDES): PASS
- Negative tests: PASS

## Kết luận / Conclusion
Đã hoàn thành đầy đủ yêu cầu bài lab.

**Ethics & Safe Use**: Chỉ dùng cho mục đích học tập. Trong thực tế nên dùng AES thay vì DES/3DES.
