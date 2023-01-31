#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>

void Zoo::AddAnimal(Animal* animal);
void Zoo::ChangeDiet(Animal& animal, int* food);
void Zoo::ChangeHabitat(Animal* animal, int habitat);
void Zoo::ChangeHabitat(Animal& animal, int habitat);
bool Zoo::IsSameHabitat(const int* h1, const int* h2);
void Zoo::RemoveAnimal(Animal* animal);
vector<Animal*> Zoo::GetAnimals();
void Zoo::PrintAnimals();
bool Zoo::IsValidName(const Animal& animal);
void Zoo::ChangeAnimalName(Animal& animal);

#endif