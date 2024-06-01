#include <string>
#include <iostream>
#include <vector>
#include <map>

enum RoomState
{
    AVAILABLE,
    UNAVAILABLE,
};

std::string roomStateToStr(RoomState r)
{
    switch (r)
    {
    case RoomState::AVAILABLE:
        return "Свободно";
    case RoomState::UNAVAILABLE:
        return "Несвободно";
    }
}

struct Visitor
{
    std::string name;
};

struct Room
{
    int roomNum;
    int placeNum;
    RoomState state;
    Visitor visitor;
};

struct Floor
{
    int floorNum;
    std::vector<Room> rooms;
};

class Hostel
{
private:
    std::vector<Floor> _hostel;

    int getUserInput(std::string msg, std::string errMsg)
    {
        int x;
        while (true)
        {
            std::cout << msg;
            std::cin >> x;
            std::cin.ignore(32767, '\n');
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << errMsg;
                continue;
            }
            return x;
        }
    }

    void addVisitor()
    {
        int floorNum = -1;
        while (floorNum > _hostel.size() or floorNum < 1)
            floorNum = getUserInput("Номер этажа : ", "Неверный выбор. Повторите занова!\n");

        floorNum--;

        int roomNum = -1;
        while (roomNum > _hostel[floorNum].rooms.size() or roomNum < 1)
            roomNum = getUserInput("Номер комнаты : ", "Неверный выбор. Повторите занова!\n");

        roomNum--;

        if (_hostel[floorNum].rooms[roomNum].state == RoomState::UNAVAILABLE)
        {
            std::cout << "Там уже живет : " << _hostel[floorNum].rooms[roomNum].visitor.name << std::endl;
            return;
        }

        std::cout << "Имя гостя : ";
        std::string visitorName;
        std::cin >> visitorName;
        std::cin.ignore(32767, '\n');

        _hostel[floorNum].rooms[roomNum].state = RoomState::UNAVAILABLE;
        _hostel[floorNum].rooms[roomNum].visitor = Visitor{visitorName};
        std::cout << "\nДобавлено Гость: " << visitorName << "  " << "[Этаж №" << floorNum + 1 << " Комната №" << roomNum + 1 << "]\n"
                  << std::endl;
    }

    void removeVisitor()
    {
        int floorNum = -1;
        while (floorNum > _hostel.size() or floorNum < 1)
            floorNum = getUserInput("Номер этажа : ", "Неверный выбор. Повторите занова!\n");

        floorNum--;

        int roomNum = -1;
        while (roomNum > _hostel[floorNum].rooms.size() or roomNum < 1)
            roomNum = getUserInput("Номер комнаты : ", "Неверный выбор. Повторите занова!\n");

        roomNum--;

        if (_hostel[floorNum].rooms[roomNum].state == RoomState::AVAILABLE)
        {
            std::cout << "Там никто не живет!" << std::endl;
            return;
        }

        std::cout << "\nУдалено Гость: " << _hostel[floorNum].rooms[roomNum].visitor.name << "  " << "[Этаж №" << floorNum + 1 << " Комната №" << roomNum + 1 << "]\n"
                  << std::endl;
        _hostel[floorNum].rooms[roomNum].state = RoomState::AVAILABLE;
        _hostel[floorNum].rooms[roomNum].visitor = Visitor{""};
    }

    void updateVisitorData()
    {
        int floorNum = -1;
        while (floorNum > _hostel.size() or floorNum < 1)
            floorNum = getUserInput("Номер этажа : ", "Неверный выбор. Повторите занова!\n");

        floorNum--;

        int roomNum = -1;
        while (roomNum > _hostel[floorNum].rooms.size() or roomNum < 1)
            roomNum = getUserInput("Номер комнаты : ", "Неверный выбор. Повторите занова!\n");

        roomNum--;

        if (_hostel[floorNum].rooms[roomNum].state == RoomState::AVAILABLE)
        {
            std::cout << "Там никто не живет!" << std::endl;
            return;
        }

        std::cout << "Имя гостя : ";
        std::string visitorName;
        std::cin >> visitorName;
        std::cin.ignore(32767, '\n');

        std::cout << "\n"
                  << _hostel[floorNum].rooms[roomNum].visitor.name << " ---> " << visitorName << "\n"
                  << std::endl;
        _hostel[floorNum].rooms[roomNum].visitor = Visitor{visitorName};
    }

    void moveVisitor()
    {
        int floorNum1 = -1;
        while (floorNum1 > _hostel.size() or floorNum1 < 1)
            floorNum1 = getUserInput("Номер актуального этажа : ", "Неверный выбор. Повторите занова!\n");

        floorNum1--;

        int roomNum1 = -1;
        while (roomNum1 > _hostel[floorNum1].rooms.size() or roomNum1 < 1)
            roomNum1 = getUserInput("Номер актуальной комнаты : ", "Неверный выбор. Повторите занова!\n");

        roomNum1--;

        if (_hostel[floorNum1].rooms[roomNum1].state == RoomState::AVAILABLE)
        {
            std::cout << "Там никто не живет!" << std::endl;
            return;
        }

        int floorNum2 = -1;
        while (floorNum2 > _hostel.size() or floorNum2 < 1)
            floorNum2 = getUserInput("Номер этажа для переселение : ", "Неверный выбор. Повторите занова!\n");

        floorNum2--;

        int roomNum2 = -1;
        while (roomNum2 > _hostel[floorNum2].rooms.size() or roomNum2 < 1)
            roomNum2 = getUserInput("Номер комнаты для переселение : ", "Неверный выбор. Повторите занова!\n");

        roomNum2--;

        if (_hostel[floorNum2].rooms[roomNum2].state == RoomState::UNAVAILABLE)
        {
            std::cout << "Там уже живет : " << _hostel[floorNum2].rooms[roomNum2].visitor.name << std::endl;
            return;
        }

        std::cout << "\nПереселяем Гость: " << _hostel[floorNum1].rooms[roomNum1].visitor.name << "  "
                  << "[Этаж №" << floorNum1 + 1 << " Комната №" << roomNum1 + 1 << "] ----> "
                  << "[Этаж №" << floorNum2 + 1 << " Комната №" << roomNum2 + 1 << "]\n"
                  << std::endl;

        Visitor vis = _hostel[floorNum1].rooms[roomNum1].visitor;
        _hostel[floorNum1].rooms[roomNum1].state = RoomState::AVAILABLE;
        _hostel[floorNum1].rooms[roomNum1].visitor = Visitor{""};
        _hostel[floorNum2].rooms[roomNum2].state = RoomState::UNAVAILABLE;
        _hostel[floorNum2].rooms[roomNum2].visitor = vis;
    }

public:
    Hostel(std::vector<Floor> hostel)
    {
        _hostel = hostel;
    }

    void printHostel()
    {
        for (const auto &floor : _hostel)
        {
            std::cout << "Этаж №" << floor.floorNum << ":\n";
            for (const auto &room : floor.rooms)
            {
                std::cout << "\tКомната №" << room.roomNum << "  : "
                          << roomStateToStr(room.state)
                          << " [Мест в комнате - " << room.placeNum << "] "
                          << ((room.state == RoomState::UNAVAILABLE) ? "Гость : " + room.visitor.name : "")
                          << std::endl;
            }
        }
    }

    void managment()
    {
        while (true)
        {
            std::cout << std::endl;
            std::cout << "1) Добавить гостя\n";
            std::cout << "2) Удалить гостя\n";
            std::cout << "3) Обнавить данные гостя\n";
            std::cout << "4) Переселить гостя\n";
            std::cout << "5) Выводить инфо о комнатах\n";
            std::cout << std::endl;

            int managerChoice = -1;
            while (managerChoice > 5 or managerChoice < 0)
                managerChoice = getUserInput("Что вы хотите сделать : ", "Неверный выбор. Повторите занова!\n");

            switch (managerChoice)
            {
            case 1:
                addVisitor();
                break;
            case 2:
                removeVisitor();
                break;
            case 3:
                updateVisitorData();
                break;
            case 4:
                moveVisitor();
                break;
            case 5:
                printHostel();
                break;
            }
        }
    }
};

int main()
{
    Hostel hostel({
        Floor{1,
              std::vector<Room>{
                  Room{1, 1, RoomState::AVAILABLE, Visitor{""}},
                  Room{2, 2, RoomState::AVAILABLE, Visitor{""}},
                  Room{3, 2, RoomState::AVAILABLE, Visitor{""}},
                  Room{4, 3, RoomState::AVAILABLE, Visitor{""}},
              }},
        Floor{2,
              std::vector<Room>{
                  Room{1, 1, RoomState::AVAILABLE, Visitor{""}},
                  Room{2, 3, RoomState::AVAILABLE, Visitor{""}},
              }},
        Floor{3,
              std::vector<Room>{
                  Room{1, 2, RoomState::AVAILABLE, Visitor{""}},
                  Room{2, 2, RoomState::AVAILABLE, Visitor{""}},
                  Room{3, 2, RoomState::AVAILABLE, Visitor{""}},
              }},
    });
    hostel.printHostel();
    hostel.managment();
}
