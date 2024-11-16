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


