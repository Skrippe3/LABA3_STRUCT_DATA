#include <iostream>
#include <set>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

struct Position {
    int x, y;
};


bool isVisited(Position* history, int historyCount, Position pos) { //через массив
    for (int i = 0; i < historyCount; ++i) {
        if (history[i].x == pos.x && history[i].y == pos.y)
            return true;
    }
    return false;
}


struct Node {   //через список
    int x, y;
    Node* next;
    Node(int x, int y, Node* next = nullptr) : x(x), y(y), next(next) {}
};

class VisitedList {
public:
    VisitedList() : head(nullptr) {}
    ~VisitedList() { clear(); }

    bool contains(int x, int y) {
        Node* current = head;
        while (current) {
            if (current->x == x && current->y == y)
                return true;
            current = current->next;
        }
        return false;
    }

    void insert(int x, int y) {
        head = new Node(x, y, head);
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Node* head;
};



int main() {

    system("chcp 1251");

    bool flag = true;
    int choose;

    do
    {

        std::cout << "Выберите действие\n" << "1) Через массив\n" << "2) Через связанный список\n" << "3) Через STL" << std::endl;

        std::cin >> choose;

        switch (choose)
        {
            case(1):
            {
                const int N = 1000; 
                Position history[N]; 
                Position current = { 0, 0 }; 
                int historyCount = 0;

                history[historyCount++] = current; 

                for (int i = 0; i < N; ++i) {
                    std::string move;
                    std::cout << "Введите направление #" << i + 1 << " (например, вверх, вниз и т.д.): ";
                    std::cin >> move;


                    if (move == "вверх") current.y++;
                    else if (move == "вниз") current.y--;
                    else if (move == "влево") current.x--;
                    else if (move == "вправо") current.x++;
                    else if (move == "вверх-влево") { current.y++; current.x--; }
                    else if (move == "вверх-вправо") { current.y++; current.x++; }
                    else if (move == "вниз-влево") { current.y--; current.x--; }
                    else if (move == "вниз-вправо") { current.y--; current.x++; }
                    else {
                        std::cout << "Некорректный ход.\n";
                        continue;
                    }

                    if (isVisited(history, historyCount, current)) {
                        std::cout << "Король уже был здесь: (" << current.x << ", " << current.y << ")\n";
                        return 0;
                    }
                    else {
                        std::cout << "Король ещё не был здесь: (" << current.x << ", " << current.y << ")\n";
                        if (historyCount < N) {
                            history[historyCount++] = current;
                        }
                    }
                }

                return 0;
            }

            case(2):
            {

                int n;
                cout << "Введите количество ходов: ";
                cin >> n;

                vector<string> moves(n);
                cout << "Введите последовательность ходов (вверх, вниз, влево, вправо, вверх-влево, вверх-вправо, вниз-влево, вниз-вправо): " << endl;
                for (int i = 0; i < n; ++i) {
                    cin >> moves[i];
                }

                int x = 0, y = 0;
                VisitedList visited;
                visited.insert(x, y);

                for (int i = 0; i < n; ++i) {
                    if (moves[i] == "вверх") y++;
                    else if (moves[i] == "вниз") y--;
                    else if (moves[i] == "влево") x--;
                    else if (moves[i] == "вправо") x++;
                    else if (moves[i] == "вверх-влево") { x--; y++; }
                    else if (moves[i] == "вверх-вправо") { x++; y++; }
                    else if (moves[i] == "вниз-влево") { x--; y--; }
                    else if (moves[i] == "вниз-вправо") { x++; y--; }

                    if (visited.contains(x, y)) {
                        cout << "Король побывал дважды на клетке (" << x << ", " << y << ")." << endl;
                        return 0;
                    }
                    visited.insert(x, y);
                }

                cout << "Король не побывал дважды на одной и той же клетке." << endl;
                return 0;
            }
            
            case(3):
            {
                std::cout << "Введите последовательность ходов" << std::endl;

                std::map<std::string, std::pair<int, int>> directions = {
                    {"вверх", {0, 1}},
                    {"вниз", {0, -1}},
                    {"влево", {-1, 0}},
                    {"вправо", {1, 0}},
                    {"вверх-влево", {-1, 1}},
                    {"вверх-вправо", {1, 1}},
                    {"вниз-влево", {-1, -1}},
                    {"вниз-вправо", {1, -1}}
                };

                std::set<std::pair<int, int>> visited;
                std::pair<int, int> current_position = { 0, 0 };
                visited.insert(current_position);

                std::string move;

                while (std::cin >> move) {
                    auto it = directions.find(move);
                    if (it != directions.end()) {

                        current_position.first += it->second.first;
                        current_position.second += it->second.second;

                        if (!visited.insert(current_position).second) {
                            std::cout << "Король побывал дважды на поле (" << current_position.first << ", " << current_position.second << ")\n";
                            return 0;
                        }
                    }
                    else {
                        std::cout << "Недопустимое направление хода: " << move << std::endl;
                    }
                }

                std::cout << "Король не посещал ни одно поле дважды.\n";
                flag = false;
                break;
            }
           
        }

    } while (flag);

    
    return 0;
}
