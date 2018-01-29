#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <random>

// Output animation data
#define OUT_ANIM 0
// Inifinite initial temperature
#define T0_INF 1

// Length of the lattice
#define LL 64
// Number of states
#define QQ 100
// Number of Monte Carlo steps
#define MCMAX 1000000

// Types used
typedef double real;
typedef int state;

int main(){

    // Total number of spins
    size_t N = LL*LL;
    // Lattice
    std::array<state, LL*LL> lattice{};
    // Temperature
    real T = 0.8, beta = 1/T;
    // Coupling constant
    real J = 1;
    // Energy of the system
    real E, dE;
    // Magnetization of the system
    real M, dM, m;
    // Lattice index
    size_t p, p_, px, py;
    // Spin state
    state s, s_;
    // Time (MCS per lattice site)
    real t_sweep;
    // Dummy indices
    size_t t, i, j;

    // Output file
    std::ofstream Efile, Mfile, ANIMfile;
    Efile.open("energyMet.dat");
    Mfile.open("magnetMet.dat");
    ANIMfile.open("animationMet.dat");

    std::cout << "Potts model with Metropolis algorithm" << std::endl;
    std::cout << QQ << " states and " << LL<<"x"<<LL << " lattice" << std::endl;

     // Initialize random number generator
    std::random_device rd;
    std::mt19937 mt(rd());

    // Random position on lattice
    std::uniform_int_distribution<size_t> rpos(0, LL*LL-1);
    // Random initial state
    std::uniform_int_distribution<state> ristate(0, QQ-1);
    // Random state
    std::uniform_int_distribution<state> rstate(0, QQ-2);
    // Random number for Metropolis
    std::uniform_real_distribution<real> rmetrop(0.0, 1.0);

    // Initialize lattice
    #if T0_INF
    for (i = 0; i < LL; i++){
        for (j = 0; j < LL; j++){
            lattice[i*LL+j] = ristate(mt);
        }
    }
    #endif

    // Calculate initial energy
    E = 0;
    for (i = 0; i < LL; i++){
        for (j = 0; j < LL; j++){
            s = lattice[i*LL+j];
            p = i*LL + (j-1)%LL;
            if (s == lattice[p]) E -= J;
            p = i*LL + (j+1)%LL;
            if (s == lattice[p]) E -= J;
        }
    }
    std::cout << "Initial energy: E = " << E << std::endl;

    // Calculate initial magnetization
    M = 0;
    for (i = 0; i < LL; i++){
        for (j = 0; j < LL; j++){
            M += lattice[i*LL+j];
        }
    }
    m = M/N;
    std::cout << "Initial magnetization per spin: m = " << m << std::endl;

    // Monte Carlo loop
    for (t = 0; t < MCMAX; t++){
        // Select random spin
        p = rpos(mt);
        s = lattice[p];
        px = p%LL;
        py = (p-px)/LL;

        // Select random new state
        s_ = rstate(mt);
        if (s_ == s) s_++;

        // Calculate magnetization difference
        dM = s_ - s;

        // Calculate energy difference
        dE = 0;
        p_ = py*LL + (px-1)%LL;
        if (s == lattice[p_]) dE += J;
        else
            if (s_ == lattice[p_]) dE -= J;
        p_ = py*LL + (px+1)%LL;
        if (s == lattice[p_]) dE += J;
        else
            if (s_ == lattice[p_]) dE -= J;
        p_ = ((py-1)%LL)*LL + px;
        if (s == lattice[p_]) dE += J;
        else
            if (s_ == lattice[p_]) dE -= J;
        p_ = ((py+1)%LL)*LL + px;
        if (s == lattice[p_]) dE += J;
        else
            if (s_ == lattice[p_]) dE -= J;

        // Calculate acceptance
        if (dE <= 0){
            lattice[p] = s_;
            E += dE;
            M += dM;
        }
        else{
            if (rmetrop(mt) <= exp(-beta*dE)){
                lattice[p] = s_;
                E += dE;
                M += dM;
            }
        }
        
        // Output data
        t_sweep = ((real)t)/N;
        m = M/N;
        Efile << t_sweep << '\t' << E << '\t' << E*E << '\n';
        Mfile << t_sweep << '\t' << m << '\t' << m*m << '\n';

        // Animation
        #if OUT_ANIM
        if (t%10000 == 0){
        for (i = 0; i < LL; i++){
            for (j = 0; j < LL; j++){
                ANIMfile << lattice[i*LL+j] << '\t';
            }
            ANIMfile << '\n';
        }
        ANIMfile << "\n\n";}
        #endif


    }

    // Close files
    Efile.close();
    Mfile.close();
    ANIMfile.close();

    return 0;
}