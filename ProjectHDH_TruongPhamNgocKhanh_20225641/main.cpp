#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int CYLINDERS = 5000;   // Số lượng cylinders
const int REQUESTS = 1000;    // Số lượng yêu cầu

void generateRequests(vector<int>& requests) {
    requests.resize(REQUESTS);
    for (int i = 0; i < REQUESTS; i++) {
        requests[i] = rand() % CYLINDERS;
    }
}
// Hàm tính số lần di chuyển đầu đọc
int calculateHeadMovement(const vector<int>& sequence, int start) { // sequence là tham chiếu đến vecter<int>
    int movement = 0;
    int current = start;
    for (int pos : sequence) { // duyệt qua các yêu cầu (các vị trí trong đĩa) trong danh sách yêu cầu
        movement += abs(current - pos); // cộng dồn khoảng cách di chuyển
        current = pos;
    }
    return movement;
}

// FCFS - First Come First Serve --> Xử lý yêu cầu lần lượt theo thứ tự đến
int fcfs(const vector<int>& requests, int start) {
    return calculateHeadMovement(requests, start);
}

// SSTF - Shortest Seek Time First --> Xử lý yêu cầu gần đầu đĩa nhất
int sstf(vector<int> requests, int start) {
    int movement = 0;         // Biến lưu tổng số quãng đường di chuyển của đầu đọc
    int current = start;      // Vị trí hiện tại của đầu đọc, bắt đầu từ 'start'

    // Lặp đến khi danh sách yêu cầu rỗng
    while (!requests.empty()) {
        // Tìm yêu cầu gần nhất với vị trí hiện tại của đầu đọc
        auto closest = min_element(requests.begin(), requests.end(),
            [current](int a, int b) { return abs(a - current) < abs(b - current); });

        // Cập nhật tổng quãng đường di chuyển bằng khoảng cách đến yêu cầu gần nhất
        movement += abs(current - *closest);

        // Cập nhật vị trí hiện tại của đầu đọc thành vị trí của yêu cầu gần nhất
        current = *closest;

        // Xóa yêu cầu vừa xử lý khỏi danh sách
        requests.erase(closest);
    }

    return movement;           // Trả về tổng quãng đường di chuyển của đầu đọc
}

// SCAN: quét toàn bộ đĩa theo 1 chiều, đồng thời xử lý các yêu cầu. Đổi chiều khi đến cuối đĩa. Ví dụ start -> cận dưới -> start -> cận trên
int scan(vector<int> requests, int start) {
    int movement = 0;               // Tổng khoảng cách mà đầu đọc di chuyển
    requests.push_back(start);      // Thêm vị trí bắt đầu vào danh sách yêu cầu
    sort(requests.begin(), requests.end());  // Sắp xếp các yêu cầu theo thứ tự tăng dần

    // Tìm iterator tới vị trí hiện tại của đầu đọc trong danh sách yêu cầu đã sắp xếp
    auto it = find(requests.begin(), requests.end(), start);

    // Di chuyển về phía trái đến biên 0, sau đó quay lại
    // Di chuyển từ vị trí hiện tại về phía đầu (0)
    for (auto i = it; i != requests.begin(); --i) {
        movement += abs(*i - *prev(i));  // Tính khoảng cách từ vị trí hiện tại đến vị trí trước đó
    }

    movement += *it;  // Cộng khoảng cách từ vị trí hiện tại đến vị trí 0

    // Di chuyển sang phải từ vị trí tiếp theo sau `start` đến cuối danh sách
    for (auto i = it + 1; i != requests.end(); ++i) {
        movement += abs(*i - *prev(i));  // Tính khoảng cách từ vị trí hiện tại đến vị trí kế tiếp
    }

    return movement;  // Trả về tổng khoảng cách di chuyển của đầu đọc
}

//C-SCAN: Giống SCAN. Nhưng khi đến cận thì nhảy ngược luôn về cận còn lại mà không quay đầu như SCAN. ví dụ start -> cận trên -> cận dưới ->start
int cscan(vector<int> requests, int start) {
    int movement = 0;                // Tổng khoảng cách mà đầu đọc di chuyển
    requests.push_back(start);       // Thêm vị trí bắt đầu vào danh sách yêu cầu
    sort(requests.begin(), requests.end());  // Sắp xếp các yêu cầu theo thứ tự tăng dần

    // Tìm iterator tới vị trí bắt đầu của đầu đọc trong danh sách yêu cầu đã sắp xếp
    auto it = find(requests.begin(), requests.end(), start);

    // Di chuyển từ vị trí hiện tại lên đến yêu cầu cuối cùng (4999)
    for (auto i = it; i != requests.end() - 1; ++i) {
        movement += abs(*i - *next(i));  // Tính khoảng cách từ yêu cầu hiện tại đến yêu cầu kế tiếp
    }

    movement += CYLINDERS - 1 - requests.back();  // Di chuyển từ yêu cầu cuối cùng đến 4999
    movement += CYLINDERS - 1;                    // Quay đầu đọc lại về 0

    // Di chuyển từ 0 lên đến yêu cầu trước vị trí bắt đầu (theo thứ tự tăng dần)
    for (auto i = requests.begin(); i != it; ++i) {
        movement += abs(*i - *next(i));  // Tính khoảng cách từ yêu cầu hiện tại đến yêu cầu kế tiếp
    }

    return movement;  // Trả về tổng quãng đường di chuyển của đầu đọc
}
//LOOK : Giống SCAN, nhưng thay vì duyệt đến cận rồi quay đầu thì ở LOOK, đầu đĩa chỉ duyệt đến yêu cầu xa nhất rồi quay đầu.
int look(vector<int> requests, int start) {
    int movement = 0;                // Biến lưu tổng khoảng cách mà đầu đọc di chuyển
    requests.push_back(start);       // Thêm vị trí bắt đầu vào danh sách yêu cầu
    sort(requests.begin(), requests.end());  // Sắp xếp các yêu cầu theo thứ tự tăng dần

    // Tìm vị trí bắt đầu của đầu đọc trong danh sách yêu cầu đã sắp xếp
    auto it = find(requests.begin(), requests.end(), start);

    // Di chuyển từ vị trí hiện tại đến yêu cầu xa nhất theo hướng bên trái
    for (auto i = it; i != requests.begin(); --i) {
        movement += abs(*i - *prev(i));  // Tính khoảng cách giữa yêu cầu hiện tại và yêu cầu trước đó
    }

    // Di chuyển từ vị trí bắt đầu đến yêu cầu xa nhất theo hướng bên phải
    for (auto i = it + 1; i != requests.end(); ++i) {
        movement += abs(*i - *prev(i));  // Tính khoảng cách giữa yêu cầu hiện tại và yêu cầu kế tiếp
    }

    return movement;  // Trả về tổng quãng đường di chuyển của đầu đọc
}
//C-LOOK: Kết hợp giữa LOOK và C-SCAN: start -> điểm xa nhất -> điểm gần nhất ->start

int clook(vector<int> requests, int start) {
    int movement = 0;  // Biến lưu tổng khoảng cách mà đầu đọc di chuyển
    requests.push_back(start);  // Thêm vị trí bắt đầu vào danh sách yêu cầu
    sort(requests.begin(), requests.end());  // Sắp xếp các yêu cầu theo thứ tự tăng dần
    auto it = find(requests.begin(), requests.end(), start);  // Tìm vị trí của start trong danh sách yêu cầu
    // Di chuyển lên đến yêu cầu cuối cùng, quay lại yêu cầu đầu tiên
    for (auto i = it; i != requests.end() - 1; ++i) {
        movement += abs(*i - *next(i));  // Tính khoảng cách từ yêu cầu hiện tại đến yêu cầu kế tiếp
    }
    movement += abs(requests.back() - requests.front());  // Quay lại đầu tiên
    for (auto i = requests.begin(); i != it; ++i) {
        movement += abs(*i - *next(i));  // Tính khoảng cách từ yêu cầu hiện tại đến yêu cầu kế tiếp
    }
    return movement;  // Trả về tổng khoảng cách di chuyển
}
int main() {
    int start;
    cout << "Nhap vi tri hien tai cua dau dia(0-4999): ";
    cin >> start;

    // Kiểm tra giá trị nhập vào
    if (start < 0 || start >= CYLINDERS) {
        cerr << "Loi! Vi tri hien tai cua dau dia phai nam trong khoang 0-4999" << endl;
        return 1;
    }

    srand(time(0));  // Khởi tạo seed cho hàm random
    vector<int> requests;
    generateRequests(requests);

    cout << "FCFS head movement: " << fcfs(requests, start) << endl;
    cout << "SSTF head movement: " << sstf(requests, start) << endl;
    cout << "SCAN head movement: " << scan(requests, start) << endl;
    cout << "C-SCAN head movement: " << cscan(requests, start) << endl;
    cout << "LOOK head movement: " << look(requests, start) << endl;
    cout << "C-LOOK head movement: " << clook(requests, start) << endl;

    return 0;
}
