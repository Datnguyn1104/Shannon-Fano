# Shannon-Fano

Ý tưởng:

1. Tin x được tạo thành từ tên x, number là số thứ tự, xác suất, 1 vector "bin" để tạo nên từ mã hoàn chỉnh.
2. Tạo ra 1 mảng động để lưu trữ tin x nhập vào từ bàn phím.
3. Sắp xếp lại nguồn tin theo thứ tự xác suất giảm dần.
4. Chia nguồn tin thành 2 nhóm có tổng xác suất xấp xỉ bằng nhau. Tiếp tục sử dụng đệ quy với 2 nhóm vừa chia (đánh số lần lượt cho mỗi 2 nhóm tạo ra là 0 và 1).
5. In ra từ mã hoàn chỉnh cho mỗi tin.
6. Tính entropy H(X), độ dài từ mã trung bình, hệ số nén thống kê (Kt)