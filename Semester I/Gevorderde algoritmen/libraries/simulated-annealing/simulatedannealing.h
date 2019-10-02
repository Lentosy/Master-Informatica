#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <random>
#include <memory>
#include <iostream>
#include <cassert>
#include <iomanip>

// Abstracte klasse voor simulated annealing
// Hier worden GEEN probleemafhankelijke functies gedefinieerd,
// deze zijn allemaal virtual.
// Notaties: zie Blum and Roli
// Parameter S: De oplossing (zowel de voorlopige als de uiteindelijke)
//              is een S. S staat voor Search space

template <class S>
class SimulatedAnnealing
{
public:
    S oplossing();

protected:
    virtual double T0() = 0; // Initiele temperatuur
    virtual bool terminate_condition(double T) = 0; // true als stoppen met zoeken
    virtual double f(const S&) = 0; // Objectieffunctie. Moet > 0 blijven
    virtual S initial_solution() = 0;
    virtual S pick_at_random(const S&) = 0;
    virtual double p(double T, double deltaf) = 0; // Probabiliteitsverandering
    virtual double update_T(double T, int i) = 0;
};

template <class S>
S SimulatedAnnealing<S>::oplossing()
{
    std::random_device rand_dev;
    std::mt19937 engine{rand_dev()};
    std::uniform_real_distribution<double> distr{0.0, 1.0};

    double T = T0(); // Temperatuur;
    S s = initial_solution(); // Voorlopige en eindoplossing.
    double cost_s = f(s);
    double min_cost = cost_s;

    int iteration = 0;
    while (!terminate_condition(T))
    {
        S s_random = pick_at_random(s);

        double cost_s_random = f(s_random);
        double deltaf = (cost_s_random - cost_s);

        double chance = p(T, deltaf);
        assert(chance >= 0.0 && chance <= 1.0);

        if ((deltaf < 0.0) || (distr(engine) < chance))
        {
            s = std::move(s_random);
        }

        cost_s = f(s);

        if (cost_s < min_cost)
        {
            min_cost = cost_s;
        }

        T = update_T(T, iteration);

        if ((iteration % 100'000) == 0)
        {
            std::cout << "Iteration " << std::setw(10) << iteration 
                << " | " << std::setw(10) << T
                << " | " << std::setw(10) << chance 
                << " | " << std::setw(10) << cost_s 
                << " | " << min_cost << std::endl;
        }

        iteration++;
    }

    return s;
}

#endif
