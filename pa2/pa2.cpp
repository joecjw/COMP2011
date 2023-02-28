#include <iostream>
#include <cstring>
#include "cleaning_robot.h"
using namespace std;

/*
   *    COMP 2011 2021 Fall Programming Assignment 2
   *    Student Name        : CHEN,Jiawei
   *    Student ID          : 20763842
   *    Student ITSC email  : jchenfq    
   * 
   * You are not allowed to use extra library
*/

// Please do all your work in this file. You just need to submit this file.
int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
                     char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{ 
   //Base case
   if(result_map[robot_y][robot_x] == BLOCKED){
      return 0;
   }

   else if(robot_energy < 0){
      return 0;
   }

   else if(robot_x < 0 || robot_x > MAP_WIDTH-1 || robot_y < 0 || robot_y > MAP_HEIGHT-1){
      return 0;
   }

   else if(result_map[robot_y][robot_x] == CHARGER){
      robot_energy = robot_full_energy;
   }

   //Recursive case
   int b=0;
   if(result_map[robot_y][robot_x] == VISITED){
      b++;
   }

   result_map[robot_y][robot_x] = VISITED;
   int a = findMaximumPlace(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map)+
   findMaximumPlace(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map)+
   findMaximumPlace(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map)+
   findMaximumPlace(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map)+1;
   return (a-b);
}

void HelpForTask2A(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
                     char result_map[MAP_HEIGHT][MAP_WIDTH], int temp_map[MAP_HEIGHT][MAP_WIDTH])
{ 
   //Base case
   if(result_map[robot_y][robot_x] == BLOCKED){
      return;
   }

   else if(robot_energy < 0){
      return;
   }

   else if(robot_x < 0 || robot_x > MAP_WIDTH-1 || robot_y < 0 || robot_y > MAP_HEIGHT-1){
      return;
   }

   //Recursive case
   result_map[robot_y][robot_x] = VISITED;

   if(temp_map[robot_y][robot_x] > 0 ){
      if(robot_full_energy-robot_energy+1 > temp_map[robot_y][robot_x]){
         return;
      }
   }
   temp_map[robot_y][robot_x] = robot_full_energy - robot_energy + 1;

   HelpForTask2A(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map);
   HelpForTask2A(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map);
   HelpForTask2A(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map);
   HelpForTask2A(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map);
}

void HelpForTask2_3(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
         char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map4[MAP_HEIGHT][MAP_WIDTH], const char map[MAP_HEIGHT][MAP_WIDTH],
         int robot_original_x, int robot_original_y, int charger_data[3], int target_x, int target_y)
{
   //Base case
   if(result_map[robot_y][robot_x] == BLOCKED){
      return;
   }

   else if(robot_x < 0 || robot_x > MAP_WIDTH-1 || robot_y < 0 || robot_y > MAP_HEIGHT-1){
      return;
   }

   else if(robot_energy < 0){
      return;
   }

   //Recursive case
   if(result_map[robot_y][robot_x] == CHARGER){

      copyMap(temp_map4, map);   
      int a = findShortestDistance(robot_original_x, robot_original_y, robot_x, robot_y, robot_full_energy, robot_full_energy, map, temp_map4);
      if(a > charger_data[0]){
         charger_data[0] = a;
         charger_data[1] = robot_x;
         charger_data[2] = robot_y;
      }
      else if(a == charger_data[0]){
         copyMap(temp_map4, map);
         int b = findShortestDistance(charger_data[1], charger_data[2], target_x, target_y, robot_full_energy, robot_full_energy, map, temp_map4);
         copyMap(temp_map4, map);
         int c = findShortestDistance(robot_x, robot_y, target_x, target_y, robot_full_energy, robot_full_energy, map, temp_map4);
         if(b > c){
            charger_data[1] = robot_x;
            charger_data[2] = robot_y;
         }
      }
   }

   result_map[robot_y][robot_x] = VISITED;
   HelpForTask2_3(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data, target_x,target_y);
   HelpForTask2_3(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data, target_x,target_y);
   HelpForTask2_3(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data, target_x,target_y);
   HelpForTask2_3(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data, target_x,target_y);
}

int HelpForTask2B(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
                         int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   int charger_data[3] = {0,0,0};
   char temp_map4[MAP_HEIGHT][MAP_WIDTH] = {};
   copyMap(temp_map, map);
   HelpForTask2_3(robot_x, robot_y, robot_energy, robot_full_energy, temp_map, temp_map4, map, robot_x, robot_y, charger_data, target_x, target_y);

   int temp_map5[MAP_HEIGHT][MAP_WIDTH] = {0};
   copyMap(temp_map, map);
   HelpForTask2A(charger_data[1], charger_data[2], robot_energy, robot_full_energy, temp_map, temp_map5);

   if(temp_map5[target_y][target_x] != 0){
      return (temp_map5[target_y][target_x] + charger_data[0] - 1);
   }

   return HelpForTask2B(charger_data[1], charger_data[2], target_x, target_y, robot_energy, robot_full_energy, map, temp_map) + (charger_data[0]-1);
}

int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
                         int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{  
   int temp_map2[MAP_HEIGHT][MAP_WIDTH] = {0};
   char temop_map3[MAP_HEIGHT][MAP_WIDTH] = {};
   copyMap(temp_map, map);
   findMaximumPlace(robot_x, robot_y, robot_energy, robot_full_energy, temp_map, temop_map3);

   if(temp_map[target_y][target_x] != VISITED){
      return PA2_MAX_PATH;
   }

   else{
      copyMap(temp_map, map);
      HelpForTask2A(robot_x, robot_y, robot_energy, robot_full_energy, temp_map, temp_map2);
      if(temp_map[target_y][target_x] == VISITED){  
         return temp_map2[target_y][target_x];
      }

      else{
         return HelpForTask2B(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);
      }
   }
}

void HelpForTask3(int robot_x, int robot_y, int robot_energy, int robot_full_energy, int distance, int distance2, 
            int original_x, int original_y, int target_x, int target_y, char result_map[MAP_HEIGHT][MAP_WIDTH], 
               const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map10[MAP_HEIGHT][MAP_WIDTH], char result_sequence[MAX_STRING_SIZE])
{ 
   //Base case
   if(result_map[robot_y][robot_x] == BLOCKED){
      return;
   }

   else if(robot_energy < 0){
      return;
   }

   else if(robot_x < 0 || robot_x > MAP_WIDTH-1 || robot_y < 0 || robot_y > MAP_HEIGHT-1){
      return;
   }

   int a = findShortestDistance(robot_x, robot_y, target_x, target_y, robot_full_energy, robot_full_energy, map,temp_map10);

   if(a != distance){
      return;
   }

   else if(a == distance){
      if(result_sequence[distance2 - distance] == '\0'){    
         if(result_map[robot_y+1][robot_x] == VISITED){
            result_sequence[distance2 - distance - 1] = 'U';
         }

         else if(result_map[robot_y][robot_x-1] == VISITED){
            result_sequence[distance2 - distance - 1] = 'R';
         }

         else if(result_map[robot_y-1][robot_x] == VISITED){
            result_sequence[distance2 - distance - 1] = 'D';
         }

         else if(result_map[robot_y][robot_x+1] == VISITED){
            result_sequence[distance2 - distance - 1] = 'L';
         }
      }

      else if(result_sequence[distance2 - distance] != '\0'){
         return;
      }
   }
   
   result_map[robot_y][robot_x] = VISITED;

   HelpForTask3(robot_x, robot_y-1, robot_energy-1, robot_full_energy, distance-1, distance2, original_x, 
         original_y, target_x, target_y, result_map, map,temp_map10,result_sequence);
   HelpForTask3(robot_x+1, robot_y, robot_energy-1, robot_full_energy, distance-1, distance2, original_x, 
         original_y, target_x, target_y, result_map, map,temp_map10,result_sequence);
   HelpForTask3(robot_x, robot_y+1, robot_energy-1, robot_full_energy, distance-1, distance2, original_x, 
         original_y, target_x, target_y, result_map, map,temp_map10,result_sequence);
   HelpForTask3(robot_x-1, robot_y, robot_energy-1, robot_full_energy, distance-1, distance2, original_x, 
         original_y, target_x, target_y, result_map, map,temp_map10,result_sequence);
}

void help3(char result_sequence[MAX_STRING_SIZE], char temp_sequence[MAX_STRING_SIZE], int result_size, int n){
   if(temp_sequence[n] == '\0' ){
      return;
   }

   result_sequence[result_size] = temp_sequence[n];

   return help3(result_sequence, temp_sequence, result_size+1, n+1);
}

void help4(char result_sequence[MAX_STRING_SIZE], int n){
   if(n == MAX_STRING_SIZE){
      return;
   }

   result_sequence[n] = '\0';

   return help4(result_sequence, n+1);
}

void help(int robot_x, int robot_y, int robot_energy, int robot_full_energy,
            int original_x, int original_y, int target_x, int target_y, char result_map[MAP_HEIGHT][MAP_WIDTH], 
               const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map10[MAP_HEIGHT][MAP_WIDTH], char result_sequence[MAX_STRING_SIZE], int result_size)
{
   copyMap(result_map, map);
   int temp_map11[MAP_HEIGHT][MAP_WIDTH]={0};
   HelpForTask2A(robot_x, robot_y, robot_energy, robot_full_energy, result_map, temp_map11);
   if(result_map[target_y][target_x] == VISITED){
      copyMap(temp_map10, map);
      int a = findShortestDistance(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map10);
      copyMap(temp_map10, map);
      copyMap(result_map, map);
      char temp_sequence2[robot_full_energy + 1] = "";
      HelpForTask3(robot_x, robot_y, robot_energy, robot_full_energy, a, a, original_x, original_y, 
                  target_x, target_y, result_map, map, temp_map10, temp_sequence2);
      help3(result_sequence, temp_sequence2, result_size, 0);
      return;
   }

   int charger_data[3]={0};
   copyMap(temp_map10, map);
   copyMap(result_map, map);
   HelpForTask2_3(robot_x, robot_y, robot_energy, robot_full_energy,result_map, temp_map10, map,
                  original_x,  original_y, charger_data, target_x, target_y);
   copyMap(temp_map10, map);
   copyMap(result_map, map);
   char temp_sequence[charger_data[0]] = "";
   HelpForTask3(robot_x, robot_y, robot_energy, robot_full_energy, charger_data[0], charger_data[0], original_x, original_y, 
                  charger_data[1], charger_data[2], result_map, map, temp_map10, temp_sequence);

   help3(result_sequence, temp_sequence, result_size, 0);

 
   return help(charger_data[1], charger_data[2], robot_energy, robot_full_energy, charger_data[1], charger_data[2], target_x, target_y, 
                  result_map, map, temp_map10, result_sequence, result_size + charger_data[0] - 1);
}

int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
                     int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{  
   int distance = findShortestDistance(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);

   if(distance == PA2_MAX_PATH){
      return PA2_MAX_PATH;
   }

   else{
      help4(result_sequence, 0);
      if(distance - 1 <= robot_full_energy){
         char result2_map[MAP_HEIGHT][MAP_WIDTH];
         char temp_map10[MAP_HEIGHT][MAP_WIDTH];
         copyMap(result2_map, map);

         int original_x = robot_x;
         int original_y = robot_y;
         int distance2 = distance;

         HelpForTask3(robot_x, robot_y, robot_energy, robot_full_energy, distance, distance2, original_x, 
         original_y, target_x, target_y, result2_map, map, temp_map10, result_sequence);

         result_sequence[distance-1] = 'T';

         return distance;
      }

      else{
         char result2_map[MAP_HEIGHT][MAP_WIDTH];
         char temp_map10[MAP_HEIGHT][MAP_WIDTH];
         copyMap(result2_map, map);

         int original_x = robot_x;
         int original_y = robot_y;

         help(robot_x, robot_y, robot_energy, robot_full_energy, original_x, original_y,
                  target_x, target_y, result2_map, map, temp_map10, result_sequence, 0);

         result_sequence[distance-1] = 'T';

         return distance;
      }
   }
}

void HelpForTask4(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
         char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map4[MAP_HEIGHT][MAP_WIDTH], const char map[MAP_HEIGHT][MAP_WIDTH],
         int robot_original_x, int robot_original_y, int charger_data[3])
{
   //Base case
   if(result_map[robot_y][robot_x] == BLOCKED){
      return;
   }

   else if(robot_x < 0 || robot_x > MAP_WIDTH-1 || robot_y < 0 || robot_y > MAP_HEIGHT-1){
      return;
   }

   else if(robot_energy < 0){
      return;
   }

   //Recursive case
   if(result_map[robot_y][robot_x] == CHARGER){
      copyMap(temp_map4, map);   
      int a = findShortestDistance(robot_original_x, robot_original_y, robot_x, robot_y, robot_full_energy, robot_full_energy, map, temp_map4);
      if(a > charger_data[0]){
         charger_data[0] = a;
         charger_data[1] = robot_x;
         charger_data[2] = robot_y;
      }
   }

   result_map[robot_y][robot_x] = VISITED;
   HelpForTask4(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data);
   HelpForTask4(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data);
   HelpForTask4(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data);
   HelpForTask4(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map4, map, robot_original_x, robot_original_y, charger_data);
}

int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, int &target_x, int &target_y, 
               int robot_energy, int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   int charger_data[3] = {0,0,0};
   char temp_map4[MAP_HEIGHT][MAP_WIDTH] = {};
   copyMap(temp_map, map);
   HelpForTask4(robot_x, robot_y, robot_energy, robot_full_energy, temp_map, temp_map4, map, robot_original_x, robot_original_y, charger_data);
  
   if(charger_data[0] != 0){
      target_x = charger_data[1];
      target_y = charger_data[2];
      return charger_data[0];
   }

   return -1;
}