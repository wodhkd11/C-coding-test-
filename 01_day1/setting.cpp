#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread> // 멀티스레딩을 위한 헤더 추가

using namespace std;
using namespace std::chrono;

int main() {
    // 5000x5000 행렬 (연산량이 125배 증가합니다!)
    const int N = 5000;
    
    cout << "행렬 크기: " << N << " x " << N << "\n";
    cout << "랜덤 데이터로 행렬 초기화 중 (잠시만 기다려주세요)...\n\n";

    // --- 기존 2차원 벡터 ---
    vector<vector<int>> arr1(N, vector<int>(N));
    vector<vector<int>> arr2(N, vector<int>(N));
    vector<vector<int>> answer1(N, vector<int>(N, 0));
    vector<vector<int>> answer2(N, vector<int>(N, 0));

    // --- 1차원 벡터 ---
    vector<int> flat_arr1(N * N);
    vector<int> flat_arr2(N * N);
    vector<int> flat_answer(N * N, 0);
    vector<int> mt_answer(N * N, 0); // 멀티스레딩용 결과 배열

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 10);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int val = dis(gen);
            arr1[i][j] = val;
            arr2[i][j] = val;
            flat_arr1[i * N + j] = val;
            flat_arr2[i * N + j] = val;
        }
    }

    // ==========================================
    // 테스트 1: 기존 방식 (2D, i -> j -> k)
    // ==========================================
    cout << "[1] 2D i-j-k 계산 중... (약 1~2분 소요 예상, 멈춘 게 아닙니다!)\n";
    auto start1 = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += arr1[i][k] * arr2[k][j];
            }
            answer1[i][j] = sum;
        }
    }

    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1).count();
    cout << "-> 소요 시간: " << duration1 << " ms\n\n";

    // ==========================================
    // 테스트 2: 캐시 최적화 방식 (2D, i -> k -> j)
    // ==========================================
    cout << "[2] 2D i-k-j 계산 중...\n";
    auto start2 = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            int r = arr1[i][k];
            for (int j = 0; j < N; ++j) {
                answer2[i][j] += r * arr2[k][j];
            }
        }
    }

    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2).count();
    cout << "-> 소요 시간: " << duration2 << " ms\n\n";

    // ==========================================
    // 테스트 3: 1차원 배열 + 캐시 최적화 (1D, i -> k -> j)
    // ==========================================
    cout << "[3] 1D i-k-j 계산 중...\n";
    auto start3 = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            int r = flat_arr1[i * N + k]; 
            for (int j = 0; j < N; ++j) {
                flat_answer[i * N + j] += r * flat_arr2[k * N + j];
            }
        }
    }

    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(end3 - start3).count();
    cout << "-> 소요 시간: " << duration3 << " ms\n\n";

    // ==========================================
    // 테스트 4: 1차원 배열 + 캐시 최적화 + 멀티스레딩
    // ==========================================
    cout << "[4] 1D i-k-j + 멀티스레딩 (M4 코어 풀가동) 계산 중...\n";
    auto start4 = high_resolution_clock::now();

    // 현재 시스템에서 사용 가능한 CPU 코어(스레드) 개수 가져오기
    unsigned int num_threads = thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4; // 혹시나 못 가져오면 기본 4개

    vector<thread> threads;
    // 전체 행(N)을 스레드 개수만큼 나눠서 할당
    int chunk_size = N / num_threads; 

    // 각 스레드가 실행할 람다 함수 정의
    auto worker = [&](int start_row, int end_row) {
        for (int i = start_row; i < end_row; ++i) {
            for (int k = 0; k < N; ++k) {
                int r = flat_arr1[i * N + k];
                for (int j = 0; j < N; ++j) {
                    mt_answer[i * N + j] += r * flat_arr2[k * N + j];
                }
            }
        }
    };

    // 스레드 생성 및 일거리 던져주기
    for (unsigned int t = 0; t < num_threads; ++t) {
        int start_row = t * chunk_size;
        // 마지막 스레드는 남은 자투리 행까지 모두 처리
        int end_row = (t == num_threads - 1) ? N : start_row + chunk_size;
        threads.emplace_back(worker, start_row, end_row);
    }

    // 모든 스레드가 일을 마칠 때까지 대기
    for (auto& th : threads) {
        th.join();
    }

    auto end4 = high_resolution_clock::now();
    auto duration4 = duration_cast<milliseconds>(end4 - start4).count();
    cout << "-> 코어 " << num_threads << "개 사용 소요 시간: " << duration4 << " ms\n\n";

    // 검증용 출력
    cout << "(검증용) 2D: " << answer1[0][0] << ", 1D: " << flat_answer[0] << ", MT: " << mt_answer[0] << "\n";

    return 0;
}