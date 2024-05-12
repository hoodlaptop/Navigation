#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

// 역과 호선 정보를 저장하는 구조체
struct Station 
{
    string name;
    int line;
};

// 그래프 클래스
class SubwayGraph 
{
private:
    unordered_map<string, vector<pair<string, int>>> graph; // 인접 리스트로 구현된 그래프

public:
    // 엣지(간선) 추가 함수
    void addEdge(string from, string to, int weight) 
    {
        graph[from].push_back({ to, weight });
        graph[to].push_back({ from, weight }); // 양방향 연결
    }

    // A* 알고리즘을 이용한 최단 경로 찾기
    vector<string> findShortestPath(string start, string end) 
    {
        unordered_map<string, int> gScore; // 시작 노드로부터의 거리
        unordered_map<string, int> fScore; // gScore와 휴리스틱을 합친 값
        unordered_map<string, string> cameFrom; // 이전 노드를 저장

        // 초기화
        for (const auto& [station, _] : graph) 
        {
            gScore[station] = numeric_limits<int>::max(); // 무한대로 초기화
            fScore[station] = numeric_limits<int>::max();
        }
        gScore[start] = 0;
        fScore[start] = heuristic(start, end); // 휴리스틱 값 초기화

        // 우선순위 큐를 사용하여 탐색
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> openSet;
        openSet.push({ fScore[start], start });

        while (!openSet.empty())
        {
            string current = openSet.top().second;
            openSet.pop();

            if (current == end) 
            {
                return reconstructPath(cameFrom, end);
            }

            for (const auto& [neighbor, weight] : graph[current])
            {
                int tentativeGScore = gScore[current] + weight;
                if (tentativeGScore < gScore[neighbor])
                {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentativeGScore;
                    fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, end);
                    openSet.push({ fScore[neighbor], neighbor });
                }
            }
        }

        // 경로를 찾을 수 없는 경우 빈 벡터 반환
        return {};
    }

private:
    // 휴리스틱 함수 (역과 역 사이의 거리)
    int heuristic(string station1, string station2) 
    {
        // 휴리스틱으로 역과 역 사이의 거리를 사용할 수도 있고, 그래프에서의 최단 거리를 사용할 수도 있습니다.
        // 여기서는 단순히 역과 역 사이의 거리를 반환하는 것으로 대체합니다.
        // 실제로는 좌표 정보 등을 이용하여 보다 정확한 휴리스틱을 계산할 수 있습니다.
        return 1; // 각 역 간의 거리가 1로 가정
    }

    // 경로 재구성 함수
    vector<string> reconstructPath(const unordered_map<string, string>& cameFrom, string current) 
    {
        vector<string> path;
        while (cameFrom.find(current) != cameFrom.end())
        {
            path.push_back(current);
            current = cameFrom.at(current);
        }
        path.push_back(current); // 시작 역 추가
        reverse(path.begin(), path.end()); // 역순으로 되어 있는 경로를 원래 순서로 뒤집음
        return path;
    }
};

int main() 
{
    SubwayGraph subway;

    subway.addEdge("서울역(1)", "시청(1)", 2);
    subway.addEdge("서울역(1)", "서울역(4)", 5);
    subway.addEdge("시청(1)", "시청(2)", 5);
    subway.addEdge("시청(1)", "종각(1)", 3);
    subway.addEdge("종각(1)", "종로3가(1)", 1);
    subway.addEdge("종로3가(1)", "종로3가(3)", 5);
    subway.addEdge("종로3가(1)", "종로5가(1)", 2);
    subway.addEdge("종로5가(1)", "동대문(1)", 2);
    subway.addEdge("동대문(1)", "동대문(4)", 5);
    subway.addEdge("동대문(1)", "동묘앞(1)", 1);
    subway.addEdge("동묘앞(1)", "신설동(1)", 2);
    subway.addEdge("신설동(1)", "제기동(1)", 2);
    subway.addEdge("제기동(1)", "청량리(1)", 2);

    subway.addEdge("시청(2)", "을지로입구(2)", 2);
    subway.addEdge("을지로입구(2)", "을지로3가(2)", 2);
    subway.addEdge("을지로3가(2)", "을지로3가(3)", 5);
    subway.addEdge("을지로3가(2)", "을지로4가(2)", 1);
    subway.addEdge("을지로4가(2)", "동대문운동장(2)", 2);
    subway.addEdge("동대문운동장(2)", "동대문운동장(4)", 5);
    subway.addEdge("동대문운동장(2)", "신당(2)", 2);
    subway.addEdge("신당(2)", "상왕십리(2)", 2);
    subway.addEdge("상왕십리(2)", "왕십리(2)", 1);
    subway.addEdge("왕십리(2)", "한양대(2)", 2);
    subway.addEdge("한양대(2)", "뚝섬(2)", 2);
    subway.addEdge("뚝섬(2)", "성수(2)", 1);
    subway.addEdge("성수(2)", "건대입구(2)", 2);
    subway.addEdge("건대입구(2)", "구의(2)", 3);
    subway.addEdge("구의(2)", "강변(2)", 1);
    subway.addEdge("강변(2)", "성내(2)", 3);
    subway.addEdge("성내(2)", "잠실(2)", 2);
    subway.addEdge("잠실(2)", "신천(2)", 2);
    subway.addEdge("신천(2)", "종합운동장(2)", 2);
    subway.addEdge("종합운동장(2)", "삼성(2)", 2);
    subway.addEdge("삼성(2)", "선릉(2)", 2);
    subway.addEdge("선릉(2)", "역삼(2)", 2);
    subway.addEdge("역삼(2)", "강남(2)", 1);
    subway.addEdge("강남(2)", "교대(2)", 2);
    subway.addEdge("교대(2)", "교대(3)", 5);
    subway.addEdge("교대(2)", "서초(2)", 2);
    subway.addEdge("서초(2)", "방배(2)", 2);
    subway.addEdge("방배(2)", "사당(2)", 3);
    subway.addEdge("사당(2)", "사당(4)", 5);
    subway.addEdge("사당(2)", "낙성대(2)", 2);
    subway.addEdge("낙성대(2)", "서울대입구(2)", 2);
    subway.addEdge("서울대입구(2)", "봉천(2)", 2);
    subway.addEdge("봉천(2)", "신림(2)", 2);
    subway.addEdge("신림(2)", "신대방(2)", 2);
    subway.addEdge("신대방(2)", "구로디지털단지(2)", 2);
    subway.addEdge("구로디지털단지(2)", "대림(2)", 2);
    subway.addEdge("대림(2)", "신도림(2)", 3);
    subway.addEdge("신도림(2)", "문래(2)", 2);
    subway.addEdge("문래(2)", "영등포구청(2)", 2);
    subway.addEdge("영등포구청(2)", "당산(2)", 2);
    subway.addEdge("당산(2)", "합정(2)", 4);
    subway.addEdge("합정(2)", "홍대입구(2)", 2);
    subway.addEdge("홍대입구(2)", "신촌(2)", 2);
    subway.addEdge("신촌(2)", "이대(2)", 2);
    subway.addEdge("이대(2)", "아현(2)", 2);
    subway.addEdge("아현(2)", "충정로(2)", 2);
    subway.addEdge("충정로(2)", "시청(2)", 3);

    subway.addEdge("지축(3)", "구파발(3)", 4);
    subway.addEdge("구파발(3)", "연신내(3)", 2);
    subway.addEdge("연신내(3)", "불광(3)", 2);
    subway.addEdge("불광(3)", "녹번(3)", 2);
    subway.addEdge("녹번(3)", "홍제(3)", 3);
    subway.addEdge("홍제(3)", "무악재(3)", 2);
    subway.addEdge("무악재(3)", "독립문(3)", 2);
    subway.addEdge("독립문(3)", "경복궁(3)", 2);
    subway.addEdge("경복궁(3)", "안국(3)", 2);
    subway.addEdge("안국(3)", "종로3가(3)", 2);
    subway.addEdge("종로3가(3)", "을지로3가(3)", 2);
    subway.addEdge("을지로3가(3)", "충무로(3)", 1);
    subway.addEdge("충무로(3)", "충무로(4)", 5);
    subway.addEdge("충무로(3)", "동대입구(3)", 2);
    subway.addEdge("동대입구(3)", "약수(3)", 2);
    subway.addEdge("약수(3)", "금호(3)", 1);
    subway.addEdge("금호(3)", "옥수(3)", 2);
    subway.addEdge("옥수(3)", "압구정(3)", 2);
    subway.addEdge("압구정(3)", "신사(3)", 3);
    subway.addEdge("신사(3)", "잠원(3)", 2);
    subway.addEdge("잠원(3)", "고속터미널(3)", 2);
    subway.addEdge("고속터미널(3)", "교대(3)", 2);
    subway.addEdge("교대(3)", "남부터미널(3)", 2);
    subway.addEdge("남부터미널(3)", "양재(3)", 3);
    subway.addEdge("양재(3)", "매봉(3)", 2);
    subway.addEdge("매봉(3)", "도곡(3)", 2);
    subway.addEdge("도곡(3)", "대치(3)", 2);
    subway.addEdge("대치(3)", "학여울(3)", 1);
    subway.addEdge("학여울(3)", "대청(3)", 2);
    subway.addEdge("대청(3)", "일원(3)", 2);
    subway.addEdge("일원(3)", "수서(3)", 3);

    subway.addEdge("당고개(4)", "상계(4)", 2);
    subway.addEdge("상계(4)", "노원(4)", 2);
    subway.addEdge("노원(4)", "창동(4)", 2);
    subway.addEdge("창동(4)", "쌍문(4)", 2);
    subway.addEdge("쌍문(4)", "수유(4)", 3);
    subway.addEdge("수유(4)", "미아(4)", 2);
    subway.addEdge("미아(4)", "미아삼거리(4)", 2);
    subway.addEdge("미아삼거리(4)", "길음(4)", 2);
    subway.addEdge("길음(4)", "성신여대입구(4)", 3);
    subway.addEdge("성신여대입구(4)", "한성대입구(4)", 2);
    subway.addEdge("한성대입구(4)", "혜화(4)", 2);
    subway.addEdge("혜화(4)", "동대문(4)", 2);
    subway.addEdge("동대문(4)", "동대문운동장(4)", 2);
    subway.addEdge("동대문운동장(4)", "충무로(4)", 2);
    subway.addEdge("충무로(4)", "명동(4)", 1);
    subway.addEdge("명동(4)", "회현(4)", 2);
    subway.addEdge("회현(4)", "서울역(4)", 2);
    subway.addEdge("서울역(4)", "숙대입구(4)", 2);
    subway.addEdge("숙대입구(4)", "삼각지(4)", 2);
    subway.addEdge("삼각지(4)", "신용산(4)", 1);
    subway.addEdge("신용산(4)", "이촌(4)", 2);
    subway.addEdge("이촌(4)", "동작(4)", 4);
    subway.addEdge("동작(4)", "총신대입구(4)", 3);
    subway.addEdge("총신대입구(4)", "사당(4)", 2);
    subway.addEdge("사당(4)", "남태령(4)", 1);


    // 사용자 입력을 받아 출발역과 도착역 설정
    string start, end;
    cout << "출발역을 입력하세요: ";
    getline(cin, start);
    cout << "도착역을 입력하세요: ";
    getline(cin, end);

    // 최단 경로 출력
    vector<string> path = subway.findShortestPath(start, end);
    if (path.empty()) {
        cout << "경로를 찾을 수 없습니다." << endl;
    }
    else {
        cout << "최단 경로: ";
        for (const auto& station : path) {
            cout << station << " -> ";
        }
        cout << endl;
    }

    return 0;
}
