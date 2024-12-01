#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "TreeMap.h"
#include "BinaryTree.h"

using namespace std;

struct Movie {
    int movieID;
    string title;
    string genre;
    int releaseYear;
    double rating;

    bool operator==(Movie& other){
        return movieID == other.movieID &&
            title == other.title &&
            genre == other.genre &&
            releaseYear == other.releaseYear &&
            rating == other.rating;
    }

    bool operator<(Movie& other)  {
        return movieID < other.movieID;
    }
};


Movie parseLine(const string& line);

TreeMap<string, BinaryTree<Movie>> loadMoviesByGenre(string& filename);
TreeMap<int, BinaryTree<Movie>> loadMoviesByYear(string& filename);
void createIndexByGenre(TreeMap<string, BinaryTree<Movie>>& movieMap);
void createIndexByYear(TreeMap<int, BinaryTree<Movie>>& movieMap);
void viewSubset(TreeMap<string, BinaryTree<Movie>>& moviesByGenre, TreeMap<int, BinaryTree<Movie>>& moviesByYear);
void displayMovies(BinaryTree<Movie>& movies);

int main() {
    string filename = "../Movies.csv";
    TreeMap<string, BinaryTree<Movie>> moviesByGenre = loadMoviesByGenre(filename);
    TreeMap<int, BinaryTree<Movie>> moviesByYear = loadMoviesByYear(filename);

    if (moviesByGenre.size() == 0 || moviesByYear.size() == 0) {
        cerr << "No data loaded. Exiting program." << endl;
        return 1;
    }

    int choice;
    do {
        cout << "1. Create an index\n";
        cout << "2. View a subset of data\n";
        cout << "3. Exit\n";
        cout << "Select an input: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Index by:\n1. Genre\n2. Year\nSelect an input: ";
            int indexChoice;
            cin >> indexChoice;

            if (indexChoice == 1) {
                createIndexByGenre(moviesByGenre);
            }
            else if (indexChoice == 2) {
                createIndexByYear(moviesByYear);
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 2:
            viewSubset(moviesByGenre, moviesByYear);
            break;
        case 3:
            cout << "Goodbye" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

Movie parseLine(string& line) {
    stringstream ss(line);
    Movie movie;
    string temp;

    getline(ss, temp, ',');
    movie.movieID = stoi(temp);

    getline(ss, movie.title, ',');

    getline(ss, movie.genre, ',');

    getline(ss, temp, ',');
    movie.releaseYear = stoi(temp);

    getline(ss, temp, ',');
    movie.rating = stod(temp);

    return movie;
}

TreeMap<string, BinaryTree<Movie>> loadMoviesByGenre(string& filename) {
    TreeMap<string, BinaryTree<Movie>> movieMap;
    ifstream file(filename);

    string line;
    getline(file, line);

    while (getline(file, line)) {
        Movie movie = parseLine(line);

        if (!movieMap.containsKey(movie.genre)) {
            movieMap.put(movie.genre, BinaryTree<Movie>());
        }
        movieMap[movie.genre].add(movie);
    }

    file.close();
    return movieMap;
}

TreeMap<int, BinaryTree<Movie>> loadMoviesByYear(string& filename) {
    TreeMap<int, BinaryTree<Movie>> movieMap;
    ifstream file(filename);

    string line;
    getline(file, line);

    while (getline(file, line)) {
        Movie movie = parseLine(line);

        if (!movieMap.containsKey(movie.releaseYear)) {
            movieMap.put(movie.releaseYear, BinaryTree<Movie>());
        }
        movieMap[movie.releaseYear].add(movie);
    }

    file.close();
    return movieMap;
}

//setw:https://www.softwaretestinghelp.com/iomanip-functions-in-cpp/
void displayMovies(BinaryTree<Movie>& movies) {
    Movie* movieArray = movies.toArray();
    cout << left << setw(10) << "MovieID"
        << setw(35) << "Title"
        << setw(20) << "Genre"
        << setw(10) << "Year"
        << setw(10) << "Rating"
        << endl;

    cout << string(85, '-') << endl;

    
    for (int i = 0; i < movies.count(); i++) {
        Movie& movie = movieArray[i];
        cout << left << setw(10) << movie.movieID
            << setw(35) << movie.title
            << setw(20) << movie.genre
            << setw(10) << movie.releaseYear
            << setw(10) << movie.rating
            << endl;
    }

    delete[] movieArray; 
}

void createIndexByGenre(TreeMap<string, BinaryTree<Movie>>& movieMap) {
    string* genres = movieMap.keySet().toArray();

    cout << left << setw(20) << "Genre" << setw(15) << "Number of Movies" << endl;
    cout << string(35, '-') << endl;

    for (int i = 0; i < movieMap.size(); i++) {
        string genre = genres[i];
        cout << left << setw(20) << genre << setw(15) << movieMap[genre].count() << endl;
    }

    delete[] genres;
}

void createIndexByYear(TreeMap<int, BinaryTree<Movie>>& movieMap) {
    int* years = movieMap.keySet().toArray();

    cout << left << setw(20) << "Release Year" << setw(20) << "Number of Movies" << endl;
    cout << string(25, '-') << endl;

    for (int i = 0; i < movieMap.size(); i++) {
        int year = years[i];
        cout << left << setw(20) << year << setw(20) << movieMap[year].count() << endl;
    }

    delete[] years;
}

void viewSubset(TreeMap<string, BinaryTree<Movie>>& moviesByGenre, TreeMap<int, BinaryTree<Movie>>& moviesByYear) {
    cout << "Filter by:\n1. Genre\n2. Year\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter genre to filter by: ";
        string genre;
        cin.ignore();
        getline(cin, genre);

        if (!moviesByGenre.containsKey(genre)) {
            cout << "No movies found for genre: " << genre << endl;
            return;
        }

        cout << "Movies in genre '" << genre << "':\n";
        displayMovies(moviesByGenre[genre]);
    }
    else if (choice == 2) {
        cout << "Enter year to filter by: ";
        int year;
        cin >> year;

        if (!moviesByYear.containsKey(year)) {
            cout << "No movies found for year: " << year << endl;
            return;
        }

        cout << "Movies released in year '" << year << "':\n";
        displayMovies(moviesByYear[year]);
    }
    else {
        cout << "Invalid choice.\n";
    }
}