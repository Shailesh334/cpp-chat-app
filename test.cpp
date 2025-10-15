#include <iostream>
#include <thread>
using namespace std;

void f() {
    cout << "Hello from thread\n";
}

int main() {
    thread t(f);
    t.join();
}
