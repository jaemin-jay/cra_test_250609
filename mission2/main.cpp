#include <stdio.h>
#include <string>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

void selectCarType(int car_type, int *stack);
void selectEngine(int engine, int *stack);
void selectbrakeSystem(int brake_system, int *stack);
void selectSteeringSystem(int steer_system, int *stack);
void runProducedCar(const int * const stack);
void delay(int ms);

using namespace std;



#include <iostream>
#include <memory>
#include <stdexcept>

std::string vehicleStr, engineStr, brakeStr, steeringStr;
int valid = true;

// === Interface Definitions ===
class Engine {
public:
    virtual std::string getName() const = 0;
    virtual ~Engine() = default;
};

class BrakeSystem {
public:
    virtual std::string getBrand() const = 0;
    virtual ~BrakeSystem() = default;
};

class SteeringSystem {
public:
    virtual std::string getType() const = 0;
    virtual ~SteeringSystem() = default;
};

// === Concrete Implementations ===
class GMEngine : public Engine {
public:
    std::string getName() const override { return "GM"; }
};

class TOYOTAEngine : public Engine {
public:
    std::string getName() const override { return "TOYOTA"; }
};

class WIAEngine : public Engine {
public:
    std::string getName() const override { return "WIA"; }
};

class BROKENEngine : public Engine {
public:
    std::string getName() const override { return "BROKEN"; }
};

class BoschBrake : public BrakeSystem {
public:
    std::string getBrand() const override { return "Bosch_b"; }
};

class MANDOBrake : public BrakeSystem {
public:
    std::string getBrand() const override { return "MANDO"; }
};

class CONTINENTALBrake : public BrakeSystem {
public:
    std::string getBrand() const override { return "CONTINENTAL"; }
};


class BOSCHSteering : public SteeringSystem {
public:
    std::string getType() const override { return "Bosch_s"; }
};

class MOBISSteering : public SteeringSystem {
public:
    std::string getType() const override { return "MOBIS"; }
};

// === Vehicle ===
class Vehicle {
    std::unique_ptr<Engine> engine;
    std::unique_ptr<BrakeSystem> brake;
    std::unique_ptr<SteeringSystem> steering;


public:
    Vehicle(std::unique_ptr<Engine> e,
        std::unique_ptr<BrakeSystem> b,
        std::unique_ptr<SteeringSystem> s)
        : engine(std::move(e)), brake(std::move(b)), steering(std::move(s)) {
    }

    void run_test() const {
        if (valid) {
            std::cout << "Engine: " << engine->getName() << "\n";
            std::cout << "Brake: " << brake->getBrand() << "\n";
            std::cout << "Steering: " << steering->getType() << "\n";
            printf("자동차가 동작됩니다.\n");

        }
        else {
            if (engine->getName() == "BROKEN") {
                printf("엔진이 고장나있습니다.\n");
                printf("자동차가 움직이지 않습니다.\n");
                return;
            }
            printf("자동차가 동작되지 않습니다\n");
            return;
        }

    }
};

// === Enums ===
enum class VehicleType { Sedan = 1, SUV, TRUCK };
enum class EngineType { GM = 1, TOYOTA, WIA, BROKEN };
enum class BrakeType { MANDO = 1, CONTINENTAL, Bosch_b };
enum class SteeringType { Bosch_s = 1, MOBIS };

// === Creator Functions ===
std::unique_ptr<Engine> createEngine(EngineType type) {
    switch (type) {
    case EngineType::GM: return std::make_unique<GMEngine>();
    case EngineType::TOYOTA: return std::make_unique<TOYOTAEngine>();
    case EngineType::WIA: return std::make_unique<WIAEngine>();
    case EngineType::BROKEN: return std::make_unique<BROKENEngine>();
    }
    throw std::invalid_argument("Invalid engine type");
}

std::unique_ptr<BrakeSystem> createBrake(BrakeType type) {
    switch (type) {
    case BrakeType::MANDO: return std::make_unique<MANDOBrake>();
    case BrakeType::CONTINENTAL: return std::make_unique<CONTINENTALBrake>();
    case BrakeType::Bosch_b: return std::make_unique<BoschBrake>();

    }
    throw std::invalid_argument("Invalid brake type");
}

std::unique_ptr<SteeringSystem> createSteering(SteeringType type) {
    switch (type) {
    case SteeringType::Bosch_s: return std::make_unique<BOSCHSteering>();
    case SteeringType::MOBIS: return std::make_unique<MOBISSteering>();
    }

    throw std::invalid_argument("Invalid steering type");
}

// === Factory ===
class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> createVehicle(
        VehicleType vt, EngineType et, BrakeType bt, SteeringType st) {

        if (vt == VehicleType::SUV && et == EngineType::TOYOTA) {
            valid = false;
            throw std::invalid_argument("자동차 부품 조합 테스트 : FAIL\nSUV에는 TOYOTA엔진 사용 불가\n");
        }

        else if (vt == VehicleType::Sedan && bt == BrakeType::CONTINENTAL) {
            valid = false;
            throw std::invalid_argument("자동차 부품 조합 테스트 : FAIL\nSedan에는 Continental제동장치 사용 불가\n");
        }
        else if (vt == VehicleType::TRUCK && et == EngineType::WIA) {
            valid = false;
            throw std::invalid_argument("자동차 부품 조합 테스트 : FAIL\nTruck에는 WIA엔진 사용 불가\n");
        }
        else if (vt == VehicleType::TRUCK && bt == BrakeType::MANDO) {
            valid = false;
            throw std::invalid_argument("자동차 부품 조합 테스트 : FAIL\nTruck에는 Mando제동장치 사용 불가\n");
        }
        else if (bt == BrakeType::Bosch_b && st != SteeringType::Bosch_s) {
            valid = false;
            throw std::invalid_argument("자동차 부품 조합 테스트 : FAIL\n");
        }
        else if (et == EngineType::BROKEN) {
            valid = false;
        }
        else 
            valid = true;
        return std::make_unique<Vehicle>(
            createEngine(et),
            createBrake(bt),
            createSteering(st)
        );
    }
};

// === Input Parsing Helpers ===
VehicleType parseVehicleType(const std::string& s) {
    if (s == "SUV") return VehicleType::SUV;
    if (s == "Sedan") return VehicleType::Sedan;
    if (s == "TRUCK") return VehicleType::TRUCK;
    throw std::invalid_argument("Unknown vehicle type");
}

EngineType parseEngineType(const std::string& s) {
    if (s == "GM") return EngineType::GM;
    if (s == "TOYOTA") return EngineType::TOYOTA;
    if (s == "WIA") return EngineType::WIA;
    if (s == "BROKEN") return EngineType::BROKEN;
    throw std::invalid_argument("Unknown engine type");
}

BrakeType parseBrakeType(const std::string& s) {
    if (s == "Bosch_b") return BrakeType::Bosch_b;
    if (s == "MANDO") return BrakeType::MANDO;
    if (s == "CONTINENTAL") return BrakeType::CONTINENTAL;
    throw std::invalid_argument("Unknown brake type");
}

SteeringType parseSteeringType(const std::string& s) {
    if (s == "Bosch_s") return SteeringType::Bosch_s;
    if (s == "MOBIS") return SteeringType::MOBIS;
    throw std::invalid_argument("Unknown steering type");
}

enum QuestionType
{   
    QuestionType_MIN = -1,
    CarType_Q = 0,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
    QuestionType_MAX
};

enum CarType
{
    CarType_MIN = 0,
    SEDAN = 1,
    SUV,
    TRUCK,
    CarType_MAX
};

enum Engine_enum
{
    Engine_MIN = -1,
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN,
    Engine_MAX
};

enum BrakeSystem_enum
{
    BrakeSystem_MIN = -1,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    BrakeSystem_MAX
};

enum SteeringSystem_enum
{
    SteeringSystem_MIN = -1,
    BOSCH_S = 1,
    MOBIS,
    SteeringSystem_MAX
};

enum RunTest
{
    RunTest_MIN = -1,
    RUN = 1,
    TEST = 2,
    RunTest_MAX
};
void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void print_car_option()
{
    printf(CLEAR_SCREEN);
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
    printf("===============================\n");
}

void print_brake_system_option()
{
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
    printf("===============================\n");
}

void print_engine_option()
{
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
    printf("===============================\n");
}

void print_steer_system_option()
{
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
    printf("===============================\n");
}

void print_run_test()
{
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
    printf("===============================\n");
}

#define EXIT_PROGRAM    (0xdeaddead)
#define INVALID_INPUT   (0xdeadbeef)
int get_parsed_input()
{
    char buf[100];
    int step = CarType_Q;
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return EXIT_PROGRAM;
    }

    // 숫자로 된 대답인지 확인
    char* checkNumber;
    int parsed_input = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return INVALID_INPUT;
    }

    return parsed_input;
}

int is_car_type_valid(int car_type)
{
    if (car_type >= CarType_MAX || car_type <= CarType_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_engine_valid(int engine)
{
    if (engine >= Engine_MAX || engine <= Engine_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_steer_system_valid(int steer_system)
{
    if (steer_system >= SteeringSystem_MAX || steer_system <= SteeringSystem_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_brake_system_valid(int brake_system)
{
    if (brake_system >= BrakeSystem_MAX || brake_system <= BrakeSystem_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_run_test_valid(int run_test)
{
    if (run_test >= RunTest_MAX || run_test <= RunTest_MIN)
        return INVALID_INPUT;

    return 0;
}

int validate_input(int input, const int * const step)
{
    if (*step == CarType_Q && is_car_type_valid(input))
    {
        printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", CarType_MIN + 1, CarType_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }
    else if (*step == Engine_Q && is_engine_valid(input))
    {
        printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", Engine_MIN + 2, Engine_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (*step == brakeSystem_Q && is_brake_system_valid(input))
    {
        printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", BrakeSystem_MIN + 2, BrakeSystem_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (*step == SteeringSystem_Q && is_steer_system_valid(input))
    {
        printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", SteeringSystem_MIN + 2, SteeringSystem_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (*step == Run_Test && is_run_test_valid(input))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return INVALID_INPUT;
    }

    return 0;
}

#define SUCCESS (1)
#define FAIL    (0)
int go_back_to_first(int input, int *step)
{
    if (input == CarType_Q && *step == Run_Test)
    {
        *step = CarType_Q;
        return SUCCESS;
    }
    return 0;
}

int go_back_to_previous(int input, int* step)
{
    if (input == CarType_Q && *step >= Engine_Q)
    {
        *step -= 1;
        return SUCCESS;
    }
    return FAIL;
}

void selectCarType(int car_type, int *stack)
{
    stack[CarType_Q] = car_type;
    if (car_type == SEDAN) {
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
        vehicleStr = "Sedan";
    }
    if (car_type == SUV) {
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
        vehicleStr = "SUV";
    }
    if (car_type == TRUCK) {
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
        vehicleStr = "TRUCK";
    }
}

void selectEngine(int engine, int *stack)
{
    stack[Engine_Q] = engine;
    if (engine == GM) {
        printf("GM 엔진을 선택하셨습니다.\n");
        engineStr = "GM";
    }
    else if (engine == TOYOTA) {
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
        engineStr = "TOYOTA";
    }
    else if (engine == WIA) {
        printf("WIA 엔진을 선택하셨습니다.\n");
        engineStr = "WIA";
    }
    else if (engine == BROKEN) {
        printf("고장난 엔진을 선택하셨습니다.\n");
        engineStr = "BROKEN";
    }
}

void selectbrakeSystem(int brake_system, int *stack)
{
    stack[brakeSystem_Q] = brake_system;
    if (brake_system == MANDO) {
        printf("MANDO 제동장치를 선택하셨습니다.\n");
        brakeStr = "MANDO";
    }
    if (brake_system == CONTINENTAL) {
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
        brakeStr = "CONTINENTAL";
    }
    if (brake_system == BOSCH_B) {
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
        brakeStr = "Bosch_b";
    }
}

void selectSteeringSystem(int steer_system, int *stack)
{
    stack[SteeringSystem_Q] = steer_system;
    if (steer_system == BOSCH_S) {
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
        steeringStr = "Bosch_s";
    }
    if (steer_system == MOBIS) {
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
        steeringStr = "MOBIS";
    }
}

int main()
{
    int stack[10];
    int step = CarType_Q;



    while (1)
    {
        if (step == CarType_Q)
            print_car_option();
        else if (step == Engine_Q)
            print_engine_option();
        else if (step == brakeSystem_Q)
            print_brake_system_option();
        else if (step == SteeringSystem_Q)
            print_steer_system_option();
        else if (step == Run_Test)
            print_run_test();

        int input_from_user = get_parsed_input();

        if (input_from_user == EXIT_PROGRAM)
            break;
        else if (input_from_user == INVALID_INPUT)
            continue;

        if (validate_input(input_from_user, &step) == INVALID_INPUT)
            continue;

        if (go_back_to_first(input_from_user, &step) == SUCCESS)
            continue;

        if (go_back_to_previous(input_from_user, &step) == SUCCESS)
            continue;

        if (step == CarType_Q)
        {
            selectCarType(input_from_user, stack);
            delay(800);
            step = Engine_Q;
        }
        else if (step == Engine_Q)
        {
            selectEngine(input_from_user, stack);
            delay(800);
            step = brakeSystem_Q;
        }
        else if (step == brakeSystem_Q)
        {
            selectbrakeSystem(input_from_user, stack);
            delay(800);
            step = SteeringSystem_Q;
        }
        else if (step == SteeringSystem_Q)
        {
            selectSteeringSystem(input_from_user, stack);
            delay(800);
            step = Run_Test;
        }
        else if (step == Run_Test)
        {
            if (input_from_user == RUN) {
                try {
                    auto vehicle = VehicleFactory::createVehicle(
                        parseVehicleType(vehicleStr),
                        parseEngineType(engineStr),
                        parseBrakeType(brakeStr),
                        parseSteeringType(steeringStr)
                    );

                    vehicle->run_test();
                    delay(2000);
                }
                catch (exception& e) {
                    std::cout << e.what();
                    delay(2000);
                    continue;
                }
            }
            else if (input_from_user == TEST) {
                printf("Test...\n");
                delay(1500);
                try {
                    auto vehicle = VehicleFactory::createVehicle(
                        parseVehicleType(vehicleStr),
                        parseEngineType(engineStr),
                        parseBrakeType(brakeStr),
                        parseSteeringType(steeringStr)
                    );
                }
                catch (exception& e) {
                    std::cout << e.what();
                    delay(2000);
                    continue;
                }

                printf("자동차 부품 조합 테스트 결과 : PASS\n");
                delay(2000);
            }
            
        }
    }
}

