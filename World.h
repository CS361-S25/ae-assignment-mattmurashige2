#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include <typeinfo>

#include "Org.h"
#include "Cow.h"
#include "Coyote.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

    /**
     * @brief Retrieves the world’s population.
     *
     * Returns the internal vector containing smart pointers to all Organism objects in the world.
     *
     * @return emp::vector<emp::Ptr<Organism>> The population vector.
     */
    emp::vector<emp::Ptr<Organism>> getPop() {
        return pop;
    }

    /**
     * @brief Extracts an organism from the population.
     *
     * Removes the organism stored at the specified index from the population
     * and returns a smart pointer to that organism.
     *
     * @param i The index from which to extract the organism.
     * @return emp::Ptr<Organism> A smart pointer to the extracted organism, or nullptr if unoccupied.
     */
    emp::Ptr<Organism> ExtractOrganism(int i) {
        emp::Ptr<Organism> extOrg = pop[i];
        pop[i] = nullptr;
        return extOrg;
    }

    /**
     * @brief Processes each occupied organism.
     *
     * Randomly shuffles the indices of the population and calls the Process method 
     * on each occupied organism with a parameter value of 100. This ensures that 
     * the organisms are processed in a random order.
     */
    void CallProcess() {
      emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
      for (int i : schedule) {
          if (!IsOccupied(i)) {continue;}
            else {
                pop[i]->Process(100);
            }
        }
    }

    /**
     * @brief Reproduces organisms.
     *
     * Randomly shuffles the indices of the population and iterates through them to 
     * selectively reproduce organisms. The reproduction logic (such as fitness 
     * evaluation and creating offspring) is handled within the function.
     */
    void ReproduceOrgs() {
      emp::vector<size_t> schedule_rep = emp::GetPermutation(random, GetSize());
      for (int i : schedule_rep) {
        if (!IsOccupied(i)) {continue;}
        else {
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring != nullptr) {
                AddOrgAt(offspring, GetRandomNeighborPos(i));
            }
        }
      }
    }

    /**
     * @brief Adds a new organism to the world.
     *
     * Inserts a new organism into the population at an appropriate location. 
     * The function typically checks for an available slot and assigns the 
     * organism pointer to that slot.
     *
     * @param new_org A pointer or reference to the organism to be added.
     * @return bool Returns true if the organism was added successfully, false otherwise.
     */
    void AddOrg(emp::Ptr<Organism> extOrg, emp::WorldPosition wp) {
        if (IsOccupied(wp)) {
            emp::Ptr<Organism> wpOrg = pop[wp.GetIndex()];
            emp::Ptr<Organism> winOrg = extOrg->Interact(wpOrg);
            if (winOrg == extOrg) { // Make sure you're not trying to add an organism to a square that it already occupies.
                AddOrgAt(extOrg, wp);
            }
        } else {
            AddOrgAt(extOrg, wp);
        } 
    }

    /**
     * @brief Moves organisms within the world.
     *
     * Reassigns the positions of organisms in the population. This function might 
     * shift organisms to remove gaps, to reallocate space for reproduction, or 
     * to simulate movement within the environment.
     *
     * @param from The original index of the organism.
     * @param to The new index for the organism.
     * @return bool Returns true if the move was successful, false if the destination 
     *              is already occupied or indices are out of bounds.
     */
    void MoveOrgs() {
        emp::vector<size_t> schedule_move = emp::GetPermutation(random, GetSize());
      for (int i : schedule_move) {
        if (!IsOccupied(i)) {
            continue;
        }
        else {
            emp::Ptr<Organism> extOrg = ExtractOrganism(i);
            if (extOrg == nullptr) {
                std::cerr << "Error: ExtractOrganism returned nullptr at index " << i << std::endl;
                continue;
            }
            emp::WorldPosition wp = GetRandomNeighborPos(i);
            AddOrg(extOrg, wp);
        }
      }
    }

  /** @brief Updates the state of the world.
  *
  * First calls the base class Update() to process actions for each organism.
  * Then it obtains a randomized schedule and processes each occupied slot.
  * Additional world-specific update logic can be added where indicated.
  */
  void Update() {

    emp::World<Organism>::Update();

    CallProcess();
    ReproduceOrgs();
    MoveOrgs();

    }
};

#endif