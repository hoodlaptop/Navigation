#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

// ���� ȣ�� ������ �����ϴ� ����ü
struct Station 
{
    string name;
    int line;
};

// �׷��� Ŭ����
class SubwayGraph 
{
private:
    unordered_map<string, vector<pair<string, int>>> graph; // ���� ����Ʈ�� ������ �׷���

public:
    // ����(����) �߰� �Լ�
    void addEdge(string from, string to, int weight) 
    {
        graph[from].push_back({ to, weight });
        graph[to].push_back({ from, weight }); // ����� ����
    }

    // A* �˰����� �̿��� �ִ� ��� ã��
    vector<string> findShortestPath(string start, string end) 
    {
        unordered_map<string, int> gScore; // ���� ���κ����� �Ÿ�
        unordered_map<string, int> fScore; // gScore�� �޸���ƽ�� ��ģ ��
        unordered_map<string, string> cameFrom; // ���� ��带 ����

        // �ʱ�ȭ
        for (const auto& [station, _] : graph) 
        {
            gScore[station] = numeric_limits<int>::max(); // ���Ѵ�� �ʱ�ȭ
            fScore[station] = numeric_limits<int>::max();
        }
        gScore[start] = 0;
        fScore[start] = heuristic(start, end); // �޸���ƽ �� �ʱ�ȭ

        // �켱���� ť�� ����Ͽ� Ž��
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

        // ��θ� ã�� �� ���� ��� �� ���� ��ȯ
        return {};
    }

private:
    // �޸���ƽ �Լ� (���� �� ������ �Ÿ�)
    int heuristic(string station1, string station2) 
    {
        // �޸���ƽ���� ���� �� ������ �Ÿ��� ����� ���� �ְ�, �׷��������� �ִ� �Ÿ��� ����� ���� �ֽ��ϴ�.
        // ���⼭�� �ܼ��� ���� �� ������ �Ÿ��� ��ȯ�ϴ� ������ ��ü�մϴ�.
        // �����δ� ��ǥ ���� ���� �̿��Ͽ� ���� ��Ȯ�� �޸���ƽ�� ����� �� �ֽ��ϴ�.
        return 1; // �� �� ���� �Ÿ��� 1�� ����
    }

    // ��� �籸�� �Լ�
    vector<string> reconstructPath(const unordered_map<string, string>& cameFrom, string current) 
    {
        vector<string> path;
        while (cameFrom.find(current) != cameFrom.end())
        {
            path.push_back(current);
            current = cameFrom.at(current);
        }
        path.push_back(current); // ���� �� �߰�
        reverse(path.begin(), path.end()); // �������� �Ǿ� �ִ� ��θ� ���� ������ ������
        return path;
    }
};

int main() 
{
    SubwayGraph subway;

    subway.addEdge("���￪(1)", "��û(1)", 2);
    subway.addEdge("���￪(1)", "���￪(4)", 5);
    subway.addEdge("��û(1)", "��û(2)", 5);
    subway.addEdge("��û(1)", "����(1)", 3);
    subway.addEdge("����(1)", "����3��(1)", 1);
    subway.addEdge("����3��(1)", "����3��(3)", 5);
    subway.addEdge("����3��(1)", "����5��(1)", 2);
    subway.addEdge("����5��(1)", "���빮(1)", 2);
    subway.addEdge("���빮(1)", "���빮(4)", 5);
    subway.addEdge("���빮(1)", "������(1)", 1);
    subway.addEdge("������(1)", "�ż���(1)", 2);
    subway.addEdge("�ż���(1)", "���⵿(1)", 2);
    subway.addEdge("���⵿(1)", "û����(1)", 2);

    subway.addEdge("��û(2)", "�������Ա�(2)", 2);
    subway.addEdge("�������Ա�(2)", "������3��(2)", 2);
    subway.addEdge("������3��(2)", "������3��(3)", 5);
    subway.addEdge("������3��(2)", "������4��(2)", 1);
    subway.addEdge("������4��(2)", "���빮���(2)", 2);
    subway.addEdge("���빮���(2)", "���빮���(4)", 5);
    subway.addEdge("���빮���(2)", "�Ŵ�(2)", 2);
    subway.addEdge("�Ŵ�(2)", "��սʸ�(2)", 2);
    subway.addEdge("��սʸ�(2)", "�սʸ�(2)", 1);
    subway.addEdge("�սʸ�(2)", "�Ѿ��(2)", 2);
    subway.addEdge("�Ѿ��(2)", "�Ҽ�(2)", 2);
    subway.addEdge("�Ҽ�(2)", "����(2)", 1);
    subway.addEdge("����(2)", "�Ǵ��Ա�(2)", 2);
    subway.addEdge("�Ǵ��Ա�(2)", "����(2)", 3);
    subway.addEdge("����(2)", "����(2)", 1);
    subway.addEdge("����(2)", "����(2)", 3);
    subway.addEdge("����(2)", "���(2)", 2);
    subway.addEdge("���(2)", "��õ(2)", 2);
    subway.addEdge("��õ(2)", "���տ��(2)", 2);
    subway.addEdge("���տ��(2)", "�Ｚ(2)", 2);
    subway.addEdge("�Ｚ(2)", "����(2)", 2);
    subway.addEdge("����(2)", "����(2)", 2);
    subway.addEdge("����(2)", "����(2)", 1);
    subway.addEdge("����(2)", "����(2)", 2);
    subway.addEdge("����(2)", "����(3)", 5);
    subway.addEdge("����(2)", "����(2)", 2);
    subway.addEdge("����(2)", "���(2)", 2);
    subway.addEdge("���(2)", "���(2)", 3);
    subway.addEdge("���(2)", "���(4)", 5);
    subway.addEdge("���(2)", "������(2)", 2);
    subway.addEdge("������(2)", "������Ա�(2)", 2);
    subway.addEdge("������Ա�(2)", "��õ(2)", 2);
    subway.addEdge("��õ(2)", "�Ÿ�(2)", 2);
    subway.addEdge("�Ÿ�(2)", "�Ŵ��(2)", 2);
    subway.addEdge("�Ŵ��(2)", "���ε����д���(2)", 2);
    subway.addEdge("���ε����д���(2)", "�븲(2)", 2);
    subway.addEdge("�븲(2)", "�ŵ���(2)", 3);
    subway.addEdge("�ŵ���(2)", "����(2)", 2);
    subway.addEdge("����(2)", "��������û(2)", 2);
    subway.addEdge("��������û(2)", "���(2)", 2);
    subway.addEdge("���(2)", "����(2)", 4);
    subway.addEdge("����(2)", "ȫ���Ա�(2)", 2);
    subway.addEdge("ȫ���Ա�(2)", "����(2)", 2);
    subway.addEdge("����(2)", "�̴�(2)", 2);
    subway.addEdge("�̴�(2)", "����(2)", 2);
    subway.addEdge("����(2)", "������(2)", 2);
    subway.addEdge("������(2)", "��û(2)", 3);

    subway.addEdge("����(3)", "���Ĺ�(3)", 4);
    subway.addEdge("���Ĺ�(3)", "���ų�(3)", 2);
    subway.addEdge("���ų�(3)", "�ұ�(3)", 2);
    subway.addEdge("�ұ�(3)", "���(3)", 2);
    subway.addEdge("���(3)", "ȫ��(3)", 3);
    subway.addEdge("ȫ��(3)", "������(3)", 2);
    subway.addEdge("������(3)", "������(3)", 2);
    subway.addEdge("������(3)", "�溹��(3)", 2);
    subway.addEdge("�溹��(3)", "�ȱ�(3)", 2);
    subway.addEdge("�ȱ�(3)", "����3��(3)", 2);
    subway.addEdge("����3��(3)", "������3��(3)", 2);
    subway.addEdge("������3��(3)", "�湫��(3)", 1);
    subway.addEdge("�湫��(3)", "�湫��(4)", 5);
    subway.addEdge("�湫��(3)", "�����Ա�(3)", 2);
    subway.addEdge("�����Ա�(3)", "���(3)", 2);
    subway.addEdge("���(3)", "��ȣ(3)", 1);
    subway.addEdge("��ȣ(3)", "����(3)", 2);
    subway.addEdge("����(3)", "�б���(3)", 2);
    subway.addEdge("�б���(3)", "�Ż�(3)", 3);
    subway.addEdge("�Ż�(3)", "���(3)", 2);
    subway.addEdge("���(3)", "����͹̳�(3)", 2);
    subway.addEdge("����͹̳�(3)", "����(3)", 2);
    subway.addEdge("����(3)", "�����͹̳�(3)", 2);
    subway.addEdge("�����͹̳�(3)", "����(3)", 3);
    subway.addEdge("����(3)", "�ź�(3)", 2);
    subway.addEdge("�ź�(3)", "����(3)", 2);
    subway.addEdge("����(3)", "��ġ(3)", 2);
    subway.addEdge("��ġ(3)", "�п���(3)", 1);
    subway.addEdge("�п���(3)", "��û(3)", 2);
    subway.addEdge("��û(3)", "�Ͽ�(3)", 2);
    subway.addEdge("�Ͽ�(3)", "����(3)", 3);

    subway.addEdge("���(4)", "���(4)", 2);
    subway.addEdge("���(4)", "���(4)", 2);
    subway.addEdge("���(4)", "â��(4)", 2);
    subway.addEdge("â��(4)", "�ֹ�(4)", 2);
    subway.addEdge("�ֹ�(4)", "����(4)", 3);
    subway.addEdge("����(4)", "�̾�(4)", 2);
    subway.addEdge("�̾�(4)", "�̾ƻ�Ÿ�(4)", 2);
    subway.addEdge("�̾ƻ�Ÿ�(4)", "����(4)", 2);
    subway.addEdge("����(4)", "���ſ����Ա�(4)", 3);
    subway.addEdge("���ſ����Ա�(4)", "�Ѽ����Ա�(4)", 2);
    subway.addEdge("�Ѽ����Ա�(4)", "��ȭ(4)", 2);
    subway.addEdge("��ȭ(4)", "���빮(4)", 2);
    subway.addEdge("���빮(4)", "���빮���(4)", 2);
    subway.addEdge("���빮���(4)", "�湫��(4)", 2);
    subway.addEdge("�湫��(4)", "��(4)", 1);
    subway.addEdge("��(4)", "ȸ��(4)", 2);
    subway.addEdge("ȸ��(4)", "���￪(4)", 2);
    subway.addEdge("���￪(4)", "�����Ա�(4)", 2);
    subway.addEdge("�����Ա�(4)", "�ﰢ��(4)", 2);
    subway.addEdge("�ﰢ��(4)", "�ſ��(4)", 1);
    subway.addEdge("�ſ��(4)", "����(4)", 2);
    subway.addEdge("����(4)", "����(4)", 4);
    subway.addEdge("����(4)", "�ѽŴ��Ա�(4)", 3);
    subway.addEdge("�ѽŴ��Ա�(4)", "���(4)", 2);
    subway.addEdge("���(4)", "���·�(4)", 1);


    // ����� �Է��� �޾� ��߿��� ������ ����
    string start, end;
    cout << "��߿��� �Է��ϼ���: ";
    getline(cin, start);
    cout << "�������� �Է��ϼ���: ";
    getline(cin, end);

    // �ִ� ��� ���
    vector<string> path = subway.findShortestPath(start, end);
    if (path.empty()) {
        cout << "��θ� ã�� �� �����ϴ�." << endl;
    }
    else {
        cout << "�ִ� ���: ";
        for (const auto& station : path) {
            cout << station << " -> ";
        }
        cout << endl;
    }

    return 0;
}
