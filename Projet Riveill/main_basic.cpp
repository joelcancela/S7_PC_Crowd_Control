#include <iostream>
#include <getopt.h>
#include <cmath>

int main(int argc, char *argv[]) {
    int opt, bench_time, four_threads;
    double people;
    while ((opt = getopt(argc, argv, "p:t:m")) != -1) {
        switch (opt) {
            case 'p':
                //std::cout << "Option p" << std::endl;
                people = pow(2.0, strtod(optarg, NULL));
                if (people < 1 || people > 512) {
                    std::cerr << "p must be between 0 & 9";
                    return 1;
                }
                //std::cout << people;
                break;
            case 't':
                //std::cout << "Option t" << optarg << std::endl;
                four_threads = atoi(optarg);
                if (four_threads < 0 || four_threads > 1) {
                    std::cerr << "t must be either 0 or 1";
                    return 1;
                }
                //std::cout<<four_threads;
                break;
            case 'm':
                //std::cout << "Option m" << std::endl;
                bench_time = atoi(optarg);
                break;
            default:
                break;
        }
    }
    //Start simulation
    return 0;
}