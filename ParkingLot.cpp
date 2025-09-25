// Design a parking lot system
// Requirements
// 1. Multiple floors
// 2. each having multiple slots
// 3. parkVehicle(), unparkVehicle()
// 4. find nearest free slot
// 5. different vehicle size

// Classes
// 1. ParkingLot
// 2. Floor
// 3. Slot
// 4. Vehicle

// Data Structures used
// 1. Array

#include<bits/stdc++.h>
using namespace std;

enum VehicleType { BIKE, CAR, TRUCK };

class Vehicle {
protected:
    string regNumber;
    VehicleType type;
public:
    Vehicle(string reg, VehicleType t) : regNumber(reg), type(t) {}
    string getRegNumber(){ return regNumber; }
    VehicleType getType(){ return type; }
};

enum SlotSize { SMALL, MEDIUM, LARGE };

class Slot {
    string slotID;
    SlotSize size;
    Vehicle* parkedVehicle;
public:
    Slot(string id, SlotSize s): slotID(id), size(s), parkedVehicle(nullptr) {}
    
    bool isFree(){ return parkedVehicle == nullptr; }
    SlotSize getSize(){ return size; }
    string getSlotID(){ return slotID; }

    bool canFit(VehicleType t){
        if(t == BIKE && size == SMALL) return true;
        if(t == CAR && (size == MEDIUM || size == LARGE)) return true;
        if(t == TRUCK && size == LARGE) return true;
        return false;
    }

    bool park(Vehicle& v){
        if(isFree() && canFit(v.getType())){
            parkedVehicle = &v;
            return true;
        }
        return false;
    }

    bool unpark(){
        if(parkedVehicle){
            parkedVehicle = nullptr;
            return true;
        }
        return false;
    }
};


class Floor {
    string floorID;
    vector<Slot> slots;
public:
    Floor(string id, vector<Slot> s) : floorID(id), slots(s) {}
    string getFloorID(){ return floorID; }

    Slot* findNearestFreeSlot(VehicleType t){
        for(auto& slot : slots){
            if(slot.isFree() && slot.canFit(t)){
                return &slot;
            }
        }
        return nullptr;
    }

    vector<Slot>& getSlots(){ return slots; }
};


class ParkingLot {
    vector<Floor> floors;
public:
    void addFloor(Floor f){ floors.push_back(f); }

    bool parkVehicle(Vehicle& v){
        for(auto& f : floors){
            Slot* slot = f.findNearestFreeSlot(v.getType());
            if(slot != nullptr){
                slot->park(v);
                cout << "Parked " << v.getRegNumber()
                     << " at Floor " << f.getFloorID()
                     << ", Slot " << slot->getSlotID() << endl;
                return true;
            }
        }
        cout << "No free slot for " << v.getRegNumber() << endl;
        return false;
    }

    bool unparkVehicle(string reg){
        for(auto& f : floors){
            for(auto& slot : f.getSlots()){
                if(!slot.isFree() && slot.unpark()){
                    cout << "Unparked vehicle " << reg
                         << " from Floor " << f.getFloorID()
                         << ", Slot " << slot.getSlotID() << endl;
                    return true;
                }
            }
        }
        cout << "Vehicle " << reg << " not found" << endl;
        return false;
    }
};


int main(){
    // Vehicles
    Vehicle v1("V001", CAR);
    Vehicle v2("V002", BIKE);
    Vehicle v3("V003", TRUCK);

    // Slots
    Slot s1("S1", SMALL);
    Slot s2("S2", MEDIUM);
    Slot s3("S3", LARGE);

    // Floors
    Floor f1("F1", {s1, s2});
    Floor f2("F2", {s3});

    // Parking Lot
    ParkingLot lot;
    lot.addFloor(f1);
    lot.addFloor(f2);

    // Operations
    lot.parkVehicle(v1);  // Park CAR
    lot.parkVehicle(v2);  // Park BIKE
    lot.parkVehicle(v3);  // Park TRUCK

    lot.unparkVehicle("V001"); // Unpark CAR

    return 0;
}
