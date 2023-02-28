//modify and submit this file only
#include "pa3.h"
#include <iostream>
using namespace std;
//you are NOT allowed to include any additional library; see FAQ

TrainCar* createTrainHead()
{
    TrainCar* head = new TrainCar;
    head->load = 0;
    head->maxLoad = 0;
    head->next = nullptr;
    head->prev = nullptr;
    head->type = HEAD;
    return head;
}

bool addCar(TrainCar* head, int position, CarType type, int maxLoad)
{   
    int length = 0;
    for(TrainCar* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
        length++;
    }

    if(type == HEAD || position <= 0 || position > length || maxLoad <= 0){
        return false;
    }

    TrainCar* added = new TrainCar;
    added->load = 0;
    added->maxLoad = maxLoad;
    added->type = type;

    TrainCar* current_ptr = head;
    for(int i = 0; i < position-1; current_ptr = current_ptr->next, i++);

    added->next = current_ptr->next;
    added->prev = current_ptr; 
    if(current_ptr->next == nullptr){
        current_ptr->next = added;
        return true;
    }

    else{
        current_ptr->next = added;
        added->next->prev = added;
        return true;
    }
}

bool deleteCar(TrainCar* head, int position)
{
    int length = 0;
    for(TrainCar* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
        length++;
    }

    if(position >= length || position < 1){
        return false;
    }

    TrainCar* current_ptr = head;
    for(int i = 0; i < position; current_ptr = current_ptr->next, i++);

    if(current_ptr->next == nullptr){
        current_ptr->prev->next = current_ptr->next;
        delete current_ptr;
        return true;
    }
    else{
        current_ptr->next->prev = current_ptr->prev;
        current_ptr->prev->next = current_ptr->next;
        delete current_ptr;
        return true; 
    }
}

bool swapCar(TrainCar* head, int a, int b)
{
    int length = 0;
    for(TrainCar* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
        length++;
    }

    if( a >= length || b >= length || a < 1 || b < 1){
        return false;
    }

    if(a > b){
        int temp = a;
        b = a;
        a = temp;
    }
  
    int position_1 = 0;
    TrainCar* current_ptr1 = head;
    while (position_1 != a)
    {
        current_ptr1 = current_ptr1->next;
        position_1++;
    }   

    TrainCar* temp_pre = current_ptr1->prev;
    TrainCar* temp_next = current_ptr1->next;

    int position_2 = 0;
    TrainCar* current_ptr2 = head;
    while (position_2 != b)
    {
        current_ptr2 = current_ptr2->next;
        position_2++;
    }

    if(current_ptr1->next != current_ptr2 && current_ptr2->next == nullptr){
        current_ptr1->prev = current_ptr2->prev;
        current_ptr1->next = current_ptr2->next;
        current_ptr2->prev = temp_pre;
        current_ptr2->next = temp_next;

        current_ptr1->prev->next = current_ptr1;                    
        current_ptr2->next->prev = current_ptr2;
        current_ptr2->prev->next = current_ptr2;
        return true;
    }
    
    else if(current_ptr1->next !=  current_ptr2 && current_ptr2->next != nullptr){
        current_ptr1->prev = current_ptr2->prev;
        current_ptr1->next = current_ptr2->next;
        current_ptr2->prev = temp_pre;
        current_ptr2->next = temp_next;

        current_ptr1->next->prev = current_ptr1;
        current_ptr1->prev->next = current_ptr1;                    
        current_ptr2->next->prev = current_ptr2;
        current_ptr2->prev->next = current_ptr2;
        return true;
    }


    else if(current_ptr1->next == current_ptr2 && current_ptr2->next == nullptr){
        current_ptr1->prev->next = current_ptr2;

        current_ptr1->next = current_ptr2->next;
        current_ptr2->prev = current_ptr1->prev;
        current_ptr1->prev = current_ptr2;
        current_ptr2->next = current_ptr1;
        return true;
    }   

    current_ptr1->prev->next = current_ptr2;
    current_ptr2->next->prev = current_ptr1;

    current_ptr1->next = current_ptr2->next;
    current_ptr2->prev = current_ptr1->prev;
    current_ptr1->prev = current_ptr2;
    current_ptr2->next = current_ptr1;
    return true;

}

void sortTrain(TrainCar* head, bool ascending)
{
    if(ascending == true){   
        for(TrainCar* current_ptr1 = head->next; current_ptr1 != nullptr; current_ptr1 = current_ptr1->next){
            for(TrainCar* current_ptr2 = head->next; current_ptr2->next != nullptr; current_ptr2 = current_ptr2->next){
                if(current_ptr2->load > current_ptr2->next->load){
                    int temp_load = current_ptr2->load;
                    current_ptr2->load = current_ptr2->next->load;
                    current_ptr2->next->load = temp_load;

                    int temp_maxload = current_ptr2->maxLoad;
                    current_ptr2->maxLoad = current_ptr2->next->maxLoad;
                    current_ptr2->next->maxLoad = temp_maxload;

                    CarType temp_cartype = current_ptr2->type;
                    current_ptr2->type = current_ptr2->next->type;
                    current_ptr2->next->type = temp_cartype;
                }
            }
        }
    }

    else if(ascending == false){
        for(TrainCar* current_ptr1 = head->next; current_ptr1 != nullptr; current_ptr1 = current_ptr1->next){
            for(TrainCar* current_ptr2 = head->next; current_ptr2->next != nullptr; current_ptr2 = current_ptr2->next){
                if(current_ptr2->load < current_ptr2->next->load){
                    int temp_load = current_ptr2->load;
                    current_ptr2->load = current_ptr2->next->load;
                    current_ptr2->next->load = temp_load;

                    int temp_maxload = current_ptr2->maxLoad;
                    current_ptr2->maxLoad =current_ptr2->next->maxLoad;
                    current_ptr2->next->maxLoad = temp_maxload;

                    CarType temp_cartype = current_ptr2->type;
                    current_ptr2->type = current_ptr2->next->type;
                    current_ptr2->next->type = temp_cartype;
                }
            }
        }
    }
}

bool load(TrainCar* head, CarType type, int amount)
{    
    int length = 0;
    for(TrainCar* p = head; p != nullptr; p = p->next){
        length++;
    }
    
    TrainCar* type_ptr[length]={nullptr};
    int arr_length = 0;
    for(TrainCar* current_ptr_1 = head; current_ptr_1 != nullptr; current_ptr_1 = current_ptr_1->next){
        if(current_ptr_1->type == type){
            type_ptr[arr_length] = current_ptr_1;
            arr_length++;
        }
    }

    if(arr_length == 0){
        return false;
    }

    int free_space = 0;
    for(int i = 0 ; i < arr_length; i++){
        free_space += type_ptr[i]->maxLoad - type_ptr[i]->load;
    }

    if(free_space < amount){
        return false;
    }

    free_space = amount;
    for(int i = 0 ; i < arr_length; i++){

        int fillup_space = type_ptr[i]->maxLoad - type_ptr[i]->load;

        if(free_space - fillup_space >= 0){
            free_space = free_space - fillup_space;
            type_ptr[i]->load = type_ptr[i]->load + fillup_space;
        }

        else if(free_space - fillup_space < 0){
            type_ptr[i]->load = type_ptr[i]->load + free_space;
            return true;
        }
    }
    
    return true;
}

bool unload(TrainCar* head, CarType type, int amount)
{ 
    int length = 0;
    for(TrainCar* p = head; p != nullptr; p = p->next){
        length++;
    }
    
    TrainCar* type_ptr[length]={nullptr};
    int arr_length = 0;
    for(TrainCar* current_ptr_1 = head; current_ptr_1 != nullptr; current_ptr_1 = current_ptr_1->next){
        if(current_ptr_1->type == type){
            type_ptr[arr_length] = current_ptr_1;
            arr_length++;
        }
    }

    if(arr_length == 0){
        return false;
    }

    int total_amount = 0;
    for(int i = 0 ; i < arr_length; i++){
        total_amount += type_ptr[i]->load;
    }

    if(total_amount < amount){
        return false;
    }

    total_amount = amount;
    for(int i = arr_length - 1 ; i >= 0; i--){
        if(total_amount - type_ptr[i]->load >= 0){
            total_amount = total_amount - type_ptr[i]->load;
            type_ptr[i]->load = 0;
        }

        else if(total_amount - type_ptr[i]->load < 0){
            type_ptr[i]->load = type_ptr[i]->load - total_amount;
            return true;
        }
    }
    
    return true;
}

void printCargoStats(const TrainCar* head)
{
    int length = 0;
    for(TrainCar* p = head->next; p != nullptr; p = p->next){
        length++;
    }

    TrainCar* car_array[length]={nullptr};
    TrainCar* current_ptr = head->next;
    for(int i = 0; current_ptr != nullptr; current_ptr = current_ptr->next, i++){
        car_array[i] = current_ptr;
    }

    for(int i = 0; i < length - 1; i++){
        for(int j = i + 1; j < length; j++){
            if(car_array[i]->type == car_array[j]->type){
                car_array[i]->load += car_array[j]->load;
                car_array[i]->maxLoad += car_array[j]->maxLoad;
                car_array[j]->type = HEAD;
            }
        } 
    }

    const char* car_type[] = {"HEAD", "OIL", "COAL", "WOOD", "STEEL", "SUGAR"};
    
    int count = 1;
    for(int i = 0; i < length; i++){
        if(car_array[i]->type != HEAD){
            if(count != 1){
                cout<<",";
            }
            cout<< car_type[car_array[i]->type];
            cout<<":"<< car_array[i]->load;
            cout<<"/"<< car_array[i]->maxLoad;
            count++;
        }
    }
    cout<<endl;
}

void divide(const TrainCar* head,  TrainCar* results[CARGO_TYPE_COUNT])
{
    int length = 0;
    for(TrainCar* p = head->next; p != nullptr; p = p->next){
        length++;
    }

    TrainCar* car_array[length]={nullptr};
    TrainCar* current_ptr = head->next;
    for(int i = 0; current_ptr != nullptr; current_ptr = current_ptr->next, i++){
        car_array[i] = current_ptr;
    }

    for(int k = 0; k < 5; k++){
        results[k] = createTrainHead();
    }  

    int result_position = 0;
    for(int i = 0; i < length-1; i++){
        bool exist = false;
        if(i != 0){
            for(int z = i - 1; z >= 0; z--){
                if(car_array[i]->type == car_array[z]->type){
                    exist = true;
                    break;
                }
            }
        }

        if(exist == true){
            continue;
        }

        int count = 0;
        TrainCar* count_ptr[length] = {nullptr};
        for(int j = i; j < length - 1; j++){
            if(car_array[i]->type == car_array[j + 1]->type){
                count_ptr[count] = car_array[j + 1];
                count++;
            }
        }

        if(count == 0){
            addCar(results[result_position], 1,  car_array[i]->type,  car_array[i]->maxLoad);
            results[result_position]->next->load = car_array[i]->load;
            result_position++;
        }

        else if(count != 0){
            addCar(results[result_position], 1,  car_array[i]->type,  car_array[i]->maxLoad);
            results[result_position]->next->load = car_array[i]->load;

            for(int x = 0; x < count; x++){
                addCar(results[result_position], x + 2,  count_ptr[x]->type,  count_ptr[x]->maxLoad);
                TrainCar* current_ptr2 = results[result_position];
                for(int y = 0; y < x + 2; current_ptr2 = current_ptr2->next, y++);
                current_ptr2->load = count_ptr[x]->load;
            }
            result_position++;
        }
    }

    for(int m = 0; m < 5; m++){
        if(results[m]->next == nullptr){
            delete results[m];
            results[m] = nullptr;
        }
    }
}

TrainCar* optimizeForMaximumPossibleCargos(const TrainCar* head, int upperBound)
{   
    int length = 0;
    for(TrainCar* p = head->next; p != nullptr; p = p->next){
        length++;
    }

    int count = 1;
    for(int i = 0; i < length; i++){
        count *= 2;
    }

    TrainCar* sub_car[length] = {nullptr};
    int result_sum = -1;

    for (int i = 0; i < count; i++) {
        
        int sub_sum = 0; 
        TrainCar* current_ptr = head->next;
        for (int j = 0; j < length; current_ptr = current_ptr->next, j++) {
            if ((i & (1 << j)) != 0){
                sub_sum += current_ptr->load;
            }
        }

        if(sub_sum == upperBound){
            for(int j = 0; j < length; j++){
                sub_car[j] = nullptr;
            }
            
            int element = 0;
            TrainCar* current_ptr2 = head->next;
            for (int j = 0; j < length; current_ptr2 = current_ptr2->next, j++) {
                if ((i & (1 << j)) != 0){
                    sub_car[element] = current_ptr2;
                    element++;
                }
            }
            break;
        }

        else if(sub_sum != upperBound && sub_sum < upperBound){
            if(result_sum == -1){
                int element = 0;
                TrainCar* current_ptr2 = head->next;
                for (int j = 0; j < length; current_ptr2 = current_ptr2->next, j++){
                    if ((i & (1 << j)) != 0){
                        sub_car[element] = current_ptr2;
                        element++;
                    }
                }
                result_sum = sub_sum;
            }

            else{
                if(upperBound - sub_sum < upperBound - result_sum){
                    for(int j = 0; j < length; j++){
                        sub_car[j] = nullptr;
                    }

                    int element = 0;
                    TrainCar* current_ptr2 = head->next;
                    for (int j = 0; j < length; current_ptr2 = current_ptr2->next, j++){
                        if ((i & (1 << j)) != 0){
                            sub_car[element] = current_ptr2;
                            element++;
                        }
                    }
                    result_sum = sub_sum;
                }
            }
        }
    }

    TrainCar* sub_head = createTrainHead();
    for(int i = 0; i < length && sub_car[i] != nullptr; i++){
        addCar(sub_head, i + 1, sub_car[i]->type, sub_car[i]->maxLoad);
        for(TrainCar* p = sub_head; p != nullptr; p = p->next){
            if(p->next == nullptr){
                p->load = sub_car[i]->load;
            }
        }
    }
    
    return sub_head;
}

void deallocateTrain(TrainCar* head)
{
    if(head == nullptr){
        return;
    }

    deallocateTrain(head->next);

    delete head;
    head = nullptr;
}
