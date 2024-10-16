#include <iostream> // средства ввода-вывода, для стандартной консоли
#include <vector> // вектор
#include <string> // строка
#include <random> // случайное число

using namespace std;

// целевое слово
const string target = "МИР";

const string alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

const int population_size = 100;

const double mutation_rate = 0.1;


// Генерируем случайный ген
char generate_gene() {
    return alphabet[rand() % alphabet.size()];
}

// Генерируем случайную особь
string generate_individual() {
    string individual;
    for (int i = 0; i < target.size(); i++) {
        individual += generate_gene();
    }
    return individual;
}

// Генерируем популяцию особей
vector<string> generate_population(int size) {
    vector<string> population;
    for (int i = 0; i < size; i++) {
        population.push_back(generate_individual());
    }
    return population;
}

// Рассчитываем приспособленность особи
int calculate_gigachad(string individual) {
    int gigachad = 0;
    for (int i = 0; i < target.size(); i++) {
        if (individual[i] == target[i]) {
            gigachad++;
        }
    }
    return gigachad;
}

// Выбираем особь из популяции с помощью турнирного отбора
string tournament_selection(vector<string> population) {
    vector<string> candidates;
    for (int i = 0; i < 5; i++) {
        candidates.push_back(population[rand() % population.size()]);
    }

    // Находим особь с самой большой приспособленностью
    string best = candidates[0];
    for (int i = 1; i < candidates.size(); i++) {
        if (calculate_gigachad(candidates[i]) > calculate_gigachad(best)) {
            best = candidates[i];
        }
    }

    return best;
}

// Выполняем кроссинговер между двумя особями
string crossover(string parent1, string parent2) {
    int crossover_point = rand() % target.size();
    string child;
    for (int i = 0; i < crossover_point; i++) {
        child += parent1[i];
    }
    for (int i = crossover_point; i < target.size(); i++) {
        child += parent2[i];
    }

    return child;
}

// Выполняем мутацию особи 
string mutation(string individual) {
    int mutation_point = rand() % target.size();
    individual[mutation_point] = generate_gene();

    return individual;
}

// новое поколение
vector<string> evolve_population(vector<string> population) {
    vector<string> new_population;
    for (int i = 0; i < population_size; i++) {
        string parent1 = tournament_selection(population);
        string parent2 = tournament_selection(population);

        if (parent1 != parent2) {
            string child = crossover(parent1, parent2);
            if (rand() / (double)RAND_MAX < mutation_rate) {
                child = mutation(child);
            }

            new_population.push_back(child);
        }

    }

    return new_population;
}

// показ лучшей особи
string print_best_individual(vector<string> population) {
    string best_individual = population[0];
    for (int i = 1; best_individual != target && i < population.size(); i++) {
        if (calculate_gigachad(population[i]) > calculate_gigachad(best_individual)) {
            best_individual = population[i];
        }
    }
    return best_individual ;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RU");
    vector<string> population = generate_population(population_size);
    cout << print_best_individual(population) << endl;
    while (print_best_individual(population) != target) {
        population = evolve_population(population);
        cout << " ----" << endl << print_best_individual(population) << endl;
        
    }

    return 0;
}