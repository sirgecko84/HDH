# Disk Scheduling Algorithms

Đây là chương trình C++ triển khai các thuật toán lập lịch đĩa trong hệ thống máy tính. Các thuật toán được triển khai gồm có:

1. **FCFS (First Come, First Served)**  
   Thuật toán FCFS là một trong những thuật toán đơn giản nhất. Nó xử lý các yêu cầu theo thứ tự chúng được nhận vào. Đầu đọc di chuyển từ yêu cầu này đến yêu cầu tiếp theo trong danh sách.

2. **SSTF (Shortest Seek Time First)**  
   Thuật toán SSTF chọn yêu cầu có khoảng cách di chuyển ngắn nhất từ vị trí hiện tại của đầu đọc. Đây là thuật toán tìm kiếm tối ưu trong ngắn hạn nhưng có thể gây hiện tượng "starvation" đối với một số yêu cầu.

3. **SCAN (Elevator Algorithm)**  
   Thuật toán SCAN giống như hoạt động của một thang máy. Đầu đọc di chuyển theo một hướng cho đến khi đến cuối dải cylinder hoặc hết yêu cầu, sau đó đảo ngược hướng và tiếp tục xử lý yêu cầu còn lại.

4. **C-SCAN (Circular SCAN)**  
   Thuật toán C-SCAN là phiên bản cải tiến của SCAN. Thay vì đảo ngược hướng, đầu đọc quay lại đầu dải (silinder 0) sau khi di chuyển đến cuối dải và tiếp tục xử lý các yêu cầu từ đầu dải đến cuối dải.

5. **LOOK**  
   Thuật toán LOOK hoạt động giống SCAN, nhưng không di chuyển đến cuối dải mà dừng lại ở yêu cầu cuối cùng trong hướng di chuyển hiện tại. Sau khi hoàn thành, đầu đọc sẽ đảo ngược và tiếp tục.

6. **C-LOOK (Circular LOOK)**  
   Thuật toán C-LOOK là phiên bản cải tiến của LOOK, tương tự như C-SCAN. Sau khi đến yêu cầu cuối cùng, đầu đọc quay lại yêu cầu đầu tiên và tiếp tục từ đó.
## Đề bài

Chương trình triển khai các thuật toán lập lịch đĩa cho một hệ thống với các đặc điểm sau:

- **Đầu vào**:
  - Chương trình nhận vào **vị trí ban đầu của đầu đọc đĩa** (initial head position) từ bàn phím. Vị trí này phải nằm trong khoảng từ **0 đến 4999** (tương ứng với các cylinder trong đĩa).
  - Chương trình **tự động sinh ra 1000 yêu cầu** ngẫu nhiên. Mỗi yêu cầu là một cylinder (một giá trị nguyên) trong phạm vi từ 0 đến 4999.

- **Dãy yêu cầu**:
  - Chương trình sử dụng hàm **`generateRequests`** để sinh ra một dãy yêu cầu ngẫu nhiên. Mỗi yêu cầu được tạo ngẫu nhiên trong phạm vi từ 0 đến 4999 và sau đó lưu vào một mảng.
  
- **Mục tiêu**:
  - Tính toán và in ra **tổng quãng đường di chuyển** của đầu đọc đĩa khi sử dụng từng thuật toán lập lịch (FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK).


