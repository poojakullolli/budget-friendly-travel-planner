#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define NUM_PLACES 11
#define INF INT_MAX
#define MAX_HOTELS 5 // Maximum number of hotels and lodges for each place
#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define FILENAME "users.txt"
#include<unistd.h>



// Define a structure for the menu items
struct MenuItem
{
    char itemName[100];
    double price;
};

// Define a structure for the binary search tree node
struct TreeNode
{
    struct MenuItem data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode *createNode(struct MenuItem item)
 {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode != NULL)
    {
        newNode->data = item;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Function to insert a node into the binary search tree
struct TreeNode *insertNode(struct TreeNode *root, struct MenuItem item)
{
    if (root == NULL)
    {
        return createNode(item);
    }

    // Compare item names for ordering
    int compareResult = strcmp(item.itemName, root->data.itemName);

    if (compareResult < 0)
    {
        root->left = insertNode(root->left, item);
    }
    else if (compareResult > 0)
    {
        root->right = insertNode(root->right, item);
    }

    return root;
}



// Function to display menu items using in-order traversal of the binary search tree
void displayMenuBST(struct TreeNode *root, int *serialNumber)
 {
    if (root != NULL)
    {
        displayMenuBST(root->left, serialNumber);
        printf("%d. %s - $%.2f\n", ++(*serialNumber), root->data.itemName, root->data.price);
        displayMenuBST(root->right, serialNumber);
    }
}


//Function to insert into binary search tree according to price.
struct TreeNode *insert(struct TreeNode *root, struct MenuItem item)
{
    if(root==NULL)
    {
        return createNode(item);
    }
    if(item.price < root->data.price)
    {
        root->left = insert(root->left,item);
    }
    else
    {
        root->right = insert(root->right,item);
    }
    return root;
}


// function to display most expensive item in the menu.
void mostexpensiveMenuItem(struct TreeNode *root)
{
    while(root->right != NULL)
    {
        root=root->right;
    }
    printf("Most Expensive Item: %s - $%.2f\n", root->data.itemName, root->data.price);

}


//Function to display least expensive item in the menu.
void leastexpensiveMenuItem(struct TreeNode * root)
{
    while(root->left != NULL)
    {
        root=root->left;
    }
     printf("Least Expensive Item: %s - $%.2f\n", root->data.itemName, root->data.price);
}

// Function to free the memory of the binary search tree
void freeTree(struct TreeNode *root)
 {
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
// Structure to represent a user
struct User
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};


// ANSI escape codes for text colors
#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[0m"
#define BLUE_TEXT "\x1b[34m"
#define YELLOW_TEXT "\x1b[33m"
#define MAGENTA_TEXT "\x1b[35m"

// Structure to store hotel/lodge information
struct Hotel
{
    char name[50];
    double price;
    double distance; // Distance from the place in km
    int rating;
    char contact[15];// Hotel rating out of 5
};


// Funtion to find out shortest path from source to destination.
void dfs(int currentVertex, bool visited[], int path[], int pathIndex)
 {
    char *places[NUM_PLACES] =
    {
    "Navagraha Teertha",
    "Moorusavir Mutt",
    "Kittur Rani Chennamma Circle",
    "Indira Gandhi Glass House Garden",
    "Siddharoodha Math",
    "Urban Oasis Mall",
    "Nrupatunga Betta",
    "Chandramouleshwara Temple",
    "Unkal Lake",
    "ISKCON Sri Krishna Balarama Temple",
    "Nuggikeri Hanuman Temple",
};
 float graph[NUM_PLACES][NUM_PLACES] =
  {
        // Fill in the distances between places in Hubli city
        // For direct paths, put 0, for unconnected places, put INF or a high value
        {0, 16,16, 16.5, 16, 19, 20, 20, 22, 26,32},
        {16, 0, 0.65, 1, 3.2, 3.5, 4.7, 4.4, 6.5, 11, 21},
        {16, 0.65, 0, 0.5, 3.3, 3.1, 4.2, 3.9, 6, 10, 19},
        {16.5, 1, 0.5, 0, 3.4, 2.6, 4.3, 3.4, 5.5, 9.6, 19.2},
        {16, 3.2, 3.3, 3.4, 0, 2.6, 6.8, 6.1, 8.2, 12, 19.4},
        {19, 3.5, 3.1, 2.6, 2.7, 0, 5.7, 4.5, 5.9, 10, 16},
        {20, 4.7, 4.2, 4.3, 6.8, 5.7, 0, 3.5, 4.8, 8.9, 22},
        {20, 4.4, 3.9, 3.4, 6.1, 4.5, 3.5, 0, 2.4, 6.6, 19},
        {22, 6.5, 6, 5.5, 8.2, 5.9, 4.8, 2.4, 0, 5.3, 18},
        {26, 11, 10, 9.6, 12, 10, 8.9, 6.6, 5.3, 0, 13},
        {32, 21, 19, 19.2, 19.4, 16, 22, 19, 18, 13, 0}
    };
    if (!visited)
    {
        // Initialize arrays for DFS
        visited = (bool *)malloc(NUM_PLACES * sizeof(bool));
        path = (int *)malloc(NUM_PLACES * sizeof(int));

        // Mark all places as not visited
        for (int i = 0; i < NUM_PLACES; ++i)
        {
            visited[i] = false;
        }
    }

    visited[currentVertex] = true;
    path[pathIndex] = currentVertex;

    // If all places are visited, print the path
    if (pathIndex == NUM_PLACES - 1)
    {
        printf("Optimal Path to Cover All Places:\n");

        for (int i = 0; i < NUM_PLACES; ++i)
        {
            printf("%s", places[path[i]]);

            if (i < NUM_PLACES - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
     else
    {
        // Recursive DFS to find the path
        for (int i = 0; i < NUM_PLACES; ++i)
        {
            if (!visited[i] && graph[currentVertex][i] != 0)
            {
                dfs(i, visited, path, pathIndex + 1);
            }
        }
    }

    // Free memory if allocated
    if (!visited)
    {
        free(visited);
        free(path);
    }
}

//This Function displays all the places in hubli

void displayAllPlaces()
 {
    printf("All Places:\n");

char *places[NUM_PLACES] =
{
    "Navagraha Teertha",
    "Moorusavir Mutt",
    "Kittur Rani Chennamma Circle",
    "Indira Gandhi Glass House Garden",
    "Siddharoodha Math",
    "Urban Oasis Mall",
    "Nrupatunga Betta",
    "Chandramouleshwara Temple",
    "Unkal Lake",
    "ISKCON Sri Krishna Balarama Temple",
    "Nuggikeri Hanuman Temple",
};

    for (int i = 0; i < NUM_PLACES; ++i)
    {
        printf("%d. %s\n", i, places[i]);
    }
}

// Common menu for all hotels
struct MenuItem commonMenu[] =
 {
    // Soups
    {"Tomato Soup", 130.0},
    {"Veg Clear Soup", 260.0},
    {"Veg Manchow Soup", 210.0},
    {"Sweet Corn Soup",210.0},
    {"Chicken Hot and Sour Soup", 210.0},
    {"Chicken Manchow Soup", 150.0},
    {"Chicken Sweet Corn Soup", 50.0},
    {"Chicken Lemon Soup", 80.0},

    // Starters
    {"Boiled Veg Butter", 50.0},
    {"Hara Bhara Kabab", 130.0},
    {"Tandoor Gobi", 330.0},
    {"Chicken Tikka", 280.0},
    {"Chicken Banjara", 360.0},
    {"Chicken Hariyali", 310.0},
    {"Chicken Lasooni Dhaniya Tikka", 330.0},
    {"Chicken Kalmi Kabab [Single]", 280.0},
    {"Chicken Tangdi Kabab [Single]", 360.0},
    {"Chicken Tandoori", 250.0},
    {"Mutton Coriander", 230.0},
    {"Mutton Seekh Kabab", 360.0},
    {"Pomfret (SEASONAL)", 140.0},
    {"Surmai (SEASONAL)", 200.0},
    {"Prawns (SEASONAL)", 380.0},

    // Chinese Veg Starters
    {"Gobi 65", 140.0},
    {"Gobi Chilli", 330.0},
    {"Gobi Manchurian", 140.0},
    {"Paneer 65", 330.0},
    {"Paneer Chilli", 310.0},
    {"Paneer Manchurian", 330.0},
    {"Baby Corn 65", 310.0},
    {"Baby Corn Chilli", 330.0},
    {"Baby Corn Manchurian", 360.0},
    {"Mushroom 65", 250.0},
    {"Mushroom Chilli", 230.0},
    {"Mushroom Manchurian", 310.0},

    // Chinese Non-Veg Starters33
    {"Egg Chilli", 140.0},
    {"Egg Manchurian", 475.0},
    {"Chicken 65", 280.0},
    {"Chicken Manchurian", 360.0},
    {"Chicken Chilli", 310.0},
    {"Chicken Pepper", 210.0},
    {"Chicken Lollipop", 195.0},
    {"Chicken Satay", 195.0},
    {"Chicken Drumstick", 220.0},
    {"Mutton Chilli", 220.0},
    {"Mutton Pepper Dry", 220.0},

    // Main Course44
    {"Veg Hyderabadi", 230.0},
    {"Veg Kolhapuri", 250.0},
    {"Veg Makhanwala", 200.0},
    {"Veg Handi", 200.0},
    {"Veg Peshawari", 260.0},
    {"Veg Kadai", 230.0},
    {"Veg Angari", 240.0},
    {"Mushroom Masala", 250.0},
    {"Methi Malai Matar", 265.0},
    {"Makai Palak", 265.0},
    {"Kaju Masala", 290.0},
    {"Kaju Korma", 290.0},
    {"Kaju Paneer", 290.0},
    {"Palak Paneer", 290.0},
    {"Paneer Butter", 290.0},
    {"Paneer Kolhapuri", 290.0},
    {"Paneer Kadai", 290.0},
    {"Paneer Tikka Masala", 310.0},

    // DAL
    {"Dal Fry", 195.0},
    {"Dal Tadka", 220.0},
    {"Dal Kolhapuri", 220.0},
    {"Dal Palak", 220.0},

    // Non-Veg Main Course
    {"Egg Kadai", 230.0},
    {"Egg Kolhapuri", 230.0},
    {"Egg Maharaja", 260.0},
    {"Egg Kachha Masala", 260.0},
    {"Murgh Kolhapuri", 280.0},
    {"Murgh Kali Mirchi", 300.0},
    {"Murgh Makhanwala", 300.0},
    {"Murgh Patiala", 300.0},
    {"Murgh Malwani", 300.0},
    {"Mutton Hyderabadi", 340.0},
    {"Mutton Kolhapuri", 340.0},
    {"Mutton Handi", 340.0},
    {"Mutton Rogan Josh", 370.0},
    {"Mutton Keema Masala", 370.0},
    {"Mutton Malwani", 370.0},

    // Chinese Veg Main Course
    {"Diced Veg in Hot Garlic Sauce", 230.0},
    {"Mushroom in Schezwan Sauce", 230.0},
    {"Veg Sweet N Sour Sauce", 230.0},

    // Chinese Non-Veg Main Course
    {"Chicken in Hot Garlic Sauce", 310.0},
    {"Chicken Schezwan Sauce", 310.0},
    {"Chicken Manchurian Sauce", 310.0},

    // Breads
    {"Roti", 40.0},
    {"Butter Roti", 50.0},
    {"Cheese Garlic Naan", 130.0},
    {"Butter Naan", 80.0},
    {"Butter Kulcha", 50.0},
    {"Aloo Paratha", 130.0},

    // Rice and Biryani
    {"Steamed Rice", 100.0},
    {"Jeera Rice", 195.0},
    {"Dal Khichdi", 195.0},
    {"Veg Pulao", 230.0},
    {"Paneer Pulao", 230.0},
    {"Veg Biryani", 260.0},
    {"Egg Biryani", 250.0},
    {"Chicken Biryani", 310.0},
    {"Mutton Biryani", 360.0},

    // Fried Rice and Noodles
    {"Egg Fried Rice", 200.0},
    {"Egg Schezwan Fried Rice", 250.0},
    {"Chicken Fried Rice", 250.0},
    {"Chicken Schezwan Fried Rice", 250.0},
    {"Veg Hakka Noodles", 195.0},
    {"Veg Schezwan Noodles", 220.0},
    {"American Chopsuey", 260.0},
    {"Veg Chowmein", 260.0},
    {"Chicken Hakka Noodles", 230.0},
    {"Chicken Schezwan Noodles", 230.0},
    {"Chicken American Chopsuey", 280.0},
    {"Chicken Chowmein", 280.0},
    {"Special Chicken Chilli Noodles", 380.0},

    // Snacks
    {"Corn Basket", 210.0},

    // Accompaniment
    {"Garden Green Salad", 100.0},

    // Drinks (Beverages)
    {"Mineral Water [1 litre]", 16.0},
};




// Structure to store place information including hotels/lodges
struct Node
{
    char place_name[50];
    struct Hotel hotels[MAX_HOTELS];
    int num_hotels;
};

// Arrays to store place names and descriptions
char *places[NUM_PLACES] =
{
    "Navagraha Teertha",
    "Moorusavir Mutt",
    "Kittur Rani Chennamma Circle",
    "Indira Gandhi Glass House Garden",
    "Siddharoodha Math",
    "Urban Oasis Mall",
    "Nrupatunga Betta",
    "Chandramouleshwara Temple",
    "Unkal Lake",
    "ISKCON Sri Krishna Balarama Temple",
    "Nuggikeri Hanuman Temple",
};

char *descriptions[NUM_PLACES] =
{
    "Pilgrimage center with nine planetary deities.",
    "Religious site known for its cultural significance.",
    "Traffic circle named after Kittur Rani Chennamma.",
    "Botanical garden with diverse plant species.",
    "Religious site dedicated to Siddharoodha Swamy.",
    "Shopping mall featuring various stores.",
    "Hilltop offering panoramic views of Hubli.",
    "Ancient temple dedicated to Lord Shiva.",
    "Scenic lake with boating facilities.",
    "Temple dedicated to Lord Krishna and Balarama.",
    "Famous Hanuman temple known for its architecture.",

};

// Function to take User information for registration.
void registerUser(struct User users[], int* userCount)
 {
    if (*userCount == MAX_USERS)
    {
        printf("Cannot register more users. Maximum limit reached.\n");
        return;
    }

    char newUsername[MAX_USERNAME_LENGTH];
    printf("Enter username: ");
    scanf("%s", newUsername);

    // Check if the username already exists
    for (int i = 0; i < *userCount; i++)
    {
        if (strcmp(users[i].username, newUsername) == 0)
        {
            printf(RED_TEXT "Username '%s' already exists. Please login instead.\n" RESET_TEXT, newUsername);
            return;
        }
    }

    // If the username is unique, proceed with registration
    strcpy(users[*userCount].username, newUsername);

    printf("Enter password: ");
    scanf("%s", users[*userCount].password);

    printf(GREEN_TEXT "Registration successful for user %s.\n" RESET_TEXT, users[*userCount].username);

    (*userCount)++;
}


// Function to get login into the
int loginUser(struct User users[], int userCount)
 {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return 1;  // Login successful
        }
    }

    return 0;  // Login failed
}



// Global array to store place information
struct Node places_info[NUM_PLACES];

void displayHotels(int dest)
 {
    printf("\nHotels and Lodges for %s:\n", places[dest]);
    printf("\n");
    for (int i = 0; i < places_info[dest].num_hotels; i++)
    {
        printf("%d. %s - Price: %.2f - Distance: %.2f km - Rating: %d/5  \n", i + 1,
               places_info[dest].hotels[i].name, places_info[dest].hotels[i].price,
               places_info[dest].hotels[i].distance, places_info[dest].hotels[i].rating);
    }
}



void heapify(struct Hotel arr[], int n, int i, int sortBy)
 {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    switch (sortBy) {
        case 1:
            if (l < n && arr[l].price > arr[largest].price)
                largest = l;
            if (r < n && arr[r].price > arr[largest].price)
                largest = r;
            break;
    }

    if (largest != i) {
        struct Hotel temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest, sortBy);
    }
}

//To sort the hotels according to their price
void heapSort(struct Hotel arr[], int n, int sortBy)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, sortBy);

    for (int i = n - 1; i >= 0; i--)
    {
        struct Hotel temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0, sortBy);
    }
}

void merge(struct Hotel arr[], int l, int m, int r, int sortBy)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Hotel L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
        {
        switch (sortBy)
         {

            case 2:
                if (L[i].distance <= R[j].distance)
                    arr[k] = L[i++];
                else
                    arr[k] = R[j++];
                break;

        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

// to display the hotels according their distance

void mergeSort(struct Hotel arr[], int l, int r, int sortBy)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, sortBy);
        mergeSort(arr, m + 1, r, sortBy);

        // Merge the sorted halves
        merge(arr, l, m, r, sortBy);
    }
}

int partition(struct Hotel arr[], int low, int high, int sortBy)
{
    struct Hotel pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        switch (sortBy)
        {
            case 3:
                if (arr[j].rating > pivot.rating)
                {
                    i++;
                    struct Hotel temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
                break;
        }
    }

    struct Hotel temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}


// to display the hotels according to their ratings.
void quickSort(struct Hotel arr[], int low, int high, int sortBy)
{
    if (low < high) {
        int pi = partition(arr, low, high, sortBy);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1, sortBy);
        quickSort(arr, pi + 1, high, sortBy);
    }
}

void sortHotels(int dest, int sortBy)
{
    struct Hotel *hotels = places_info[dest].hotels;
    int numHotels = places_info[dest].num_hotels;

    switch (sortBy)
     {
        case 1:
            heapSort(hotels, numHotels, sortBy);
            break;
        case 2:
            mergeSort(hotels, 0, numHotels - 1, sortBy);
            break;
        case 3:
            quickSort(hotels, 0, numHotels - 1, sortBy);
            break;
    }
}


// function to ask users to enter sort by
// then displaying hotels according to their sorted order.
void displaySortedHotels(int dest)
{
    printf(MAGENTA_TEXT "\nHotels nearer to %s sorted by:\n" RESET_TEXT, places_info[dest].place_name);
    printf("1. Price\n");
    printf("2. Distance\n");
    printf("3. Rating\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf(RED_TEXT "Invalid choice. Exiting...\n" RESET_TEXT);
        exit(1);
    }

    sortHotels(dest, choice);

    printf("\n%-20s%-10s%-15s%-10s\n", "Hotel Name", "Price", "Distance", "Rating");
    for (int i = 0; i < places_info[dest].num_hotels; i++)
    {
        printf("%-20s%-10.2f%-15.2f%d/5\n",
               places_info[dest].hotels[i].name,
               places_info[dest].hotels[i].price,
               places_info[dest].hotels[i].distance,
               places_info[dest].hotels[i].rating);
    }
}


// Funtion to Initializing the hotels.
void initializeHotels()
{
    // Initialize hotels for each place
   strcpy(places_info[0].place_name, "NAVAGRAHA TEERTHA");
    places_info[0].num_hotels = 3;

    strcpy(places_info[0].hotels[0].name, "HOTEL THE CULT");
    places_info[0].hotels[0].price = 1700.0;
    places_info[0].hotels[0].distance = 1.7;
    places_info[0].hotels[0].rating = 4.0;
    strcpy(places_info[0].hotels[0].contact, "99012 24459");



     strcpy(places_info[0].hotels[1].name, "HOTEL PEACOCK");
    places_info[0].hotels[1].price = 1000.0;
    places_info[0].hotels[1].distance = 10;
    places_info[0].hotels[1].rating = 3.5;
    strcpy(places_info[0].hotels[1].contact, "74118 16122");



     strcpy(places_info[0].hotels[2].name, "HOTEL ASHOKA TOWERS");
    places_info[0].hotels[2].price = 900;
    places_info[0].hotels[2].distance = 15;
    places_info[0].hotels[2].rating = 3.5;
     strcpy(places_info[0].hotels[2].contact, "98455 57790");





    strcpy(places_info[1].place_name, "MOORUSAVIR MUTT");
    places_info[1].num_hotels = 3;

     strcpy(places_info[1].hotels[0].name, " HOTEL PEACOCK");
    places_info[1].hotels[0].price = 1000.0;
    places_info[1].hotels[0].distance = 2.3;
    places_info[1].hotels[0].rating = 3.0;
    strcpy(places_info[1].hotels[0].contact, "74118 16122");


     strcpy(places_info[1].hotels[1].name, "HOTEL ASHOKA TOWERS");
    places_info[1].hotels[1].price = 900.0;
    places_info[1].hotels[1].distance = 2.9;
    places_info[1].hotels[1].rating = 3.5;
    strcpy(places_info[1].hotels[1].contact, "98455 57790");


     strcpy(places_info[1].hotels[2].name, "SHRI VASANT LODGE");
    places_info[1].hotels[2].price = 1500;
    places_info[1].hotels[2].distance = 3.1;
    places_info[1].hotels[2].rating = 3.5;
    strcpy(places_info[1].hotels[2].contact, "88847 07684");




    strcpy(places_info[2].place_name, "KITTUR RANI CHENNAMMA CIRCLE");
    places_info[2].num_hotels = 3;

     strcpy(places_info[2].hotels[0].name, "THE BLISS HOTEL");
    places_info[2].hotels[0].price = 2600.0;
    places_info[2].hotels[0].distance = 3.0;
    places_info[2].hotels[0].rating = 4.0;
    strcpy(places_info[1].hotels[2].contact, "99806 87607");


     strcpy(places_info[2].hotels[1].name, "SHRI VASANT LODGE");
    places_info[2].hotels[1].price = 1500.0;
    places_info[2].hotels[1].distance = 2.2;
    places_info[2].hotels[1].rating = 3.5;
    strcpy(places_info[2].hotels[1].contact, "88847 07684");


     strcpy(places_info[2].hotels[2].name, "HOTEL METROPOLIS");
    places_info[2].hotels[2].price = 1700;
    places_info[2].hotels[2].distance = 2.7;
    places_info[2].hotels[2].rating = 4.0;
    strcpy(places_info[2].hotels[2].contact, "83642 66666");




    strcpy(places_info[3].place_name, "INDIRA GANDHI GLASS HOUSE GARDEN");
    places_info[3].num_hotels = 3;

    strcpy(places_info[3].hotels[0].name, "HOTEL AYODHYA");
    places_info[3].hotels[0].price = 1700.0;
    places_info[3].hotels[0].distance = 0.740;
    places_info[3].hotels[0].rating = 3.0;
    strcpy(places_info[3].hotels[0].contact, "78999 51951");


     strcpy(places_info[3].hotels[1].name, "HOTEL SHRINAGAR PALACE");
    places_info[3].hotels[1].price = 4500.0;
    places_info[3].hotels[1].distance = 2.3;
    places_info[3].hotels[1].rating = 3.5;
    strcpy(places_info[3].hotels[1].contact, "63625 67756");


     strcpy(places_info[3].hotels[2].name, "LEMON TREE HOTEL");
    places_info[3].hotels[2].price = 4000;
    places_info[3].hotels[2].distance = 2.8;
    places_info[3].hotels[2].rating = 3.5;
    strcpy(places_info[3].hotels[2].contact, "83666 16661");




    strcpy(places_info[4].place_name, "SIDDHAROODHA MATH");
    places_info[4].num_hotels = 3;

    strcpy(places_info[4].hotels[0].name, "THE FERN RESIDENCY ");
    places_info[4].hotels[0].price = 5400.0;
    places_info[4].hotels[0].distance = 2.4;
    places_info[4].hotels[0].rating = 4.0;
      strcpy(places_info[4].hotels[0].contact, "98445 00028");


     strcpy(places_info[4].hotels[1].name, "HOTEL AYODHYA");
    places_info[4].hotels[1].price = 1700.0;
    places_info[4].hotels[1].distance = 2.7;
    places_info[4].hotels[1].rating = 3.0;
    strcpy(places_info[4].hotels[1].contact, "78999 51951");


     strcpy(places_info[4].hotels[2].name, "THE OAKS COMFORTS");
    places_info[4].hotels[2].price = 2000;
    places_info[4].hotels[2].distance = 2.3;
    places_info[4].hotels[2].rating = 3.0;
    strcpy(places_info[4].hotels[2].contact, "89515 30999");




    strcpy(places_info[5].place_name, "Urban Oasis Mall");
    places_info[5].num_hotels = 4;


    strcpy(places_info[5].hotels[0].name, "CUBIX HOTEL");
    places_info[5].hotels[0].price = 3700.0;
    places_info[5].hotels[0].distance = 0.90;
    places_info[5].hotels[0].rating = 4.5;
     strcpy(places_info[5].hotels[0].contact, "83629 99999");


     strcpy(places_info[5].hotels[1].name, "THE BLISS HOTEL");
    places_info[5].hotels[1].price = 2600.0;
    places_info[5].hotels[1].distance = 0.510;
    places_info[5].hotels[1].rating = 4.0;
     strcpy(places_info[5].hotels[1].contact, "99806 87607");


     strcpy(places_info[5].hotels[2].name, "SKD COMFORTS");
    places_info[5].hotels[2].price = 1600.0;
    places_info[5].hotels[2].distance = 2.1;
    places_info[5].hotels[2].rating = 3.6;
     strcpy(places_info[5].hotels[2].contact, "83648 50301");


     strcpy(places_info[5].hotels[3].name, "HOTEL PEACOCK");
    places_info[5].hotels[3].price = 1000.0;
    places_info[5].hotels[3].distance = 2.5;
    places_info[5].hotels[3].rating = 3.5;
    strcpy(places_info[5].hotels[3].contact, "74118 16122");



     strcpy(places_info[6].place_name, "Nrupatunga Betta");
    places_info[6].num_hotels = 2;

    strcpy(places_info[6].hotels[0].name, "SKD COMFORTS");
    places_info[6].hotels[0].price = 1600.0;
    places_info[6].hotels[0].distance = 2.5;
    places_info[6].hotels[0].rating = 3.6;
     strcpy(places_info[6].hotels[0].contact, "83648 50301");



     strcpy(places_info[6].hotels[1].name, "THE PRESIDENT HOTEL");
    places_info[6].hotels[1].price = 4400.0;
    places_info[6].hotels[1].distance = 4.0;
    places_info[6].hotels[1].rating = 4.0;
      strcpy(places_info[6].hotels[0].contact, "83622 34888");



  strcpy(places_info[7].place_name, "Chandramouleshwara Temple");
    places_info[7].num_hotels = 3;


    strcpy(places_info[7].hotels[0].name, "THE PRESIDENT HOTEL");
    places_info[7].hotels[0].price = 4400.0;
    places_info[7].hotels[0].distance = 0.66;
    places_info[7].hotels[0].rating = 4.0;
    places_info[7].hotels[0].contact, "83622 34888";



     strcpy(places_info[7].hotels[1].name, "HOTEL PEACOCK");
    places_info[7].hotels[1].price = 1000;
    places_info[7].hotels[1].distance = 3.2;
    places_info[7].hotels[1].rating = 3.5;
     strcpy(places_info[7].hotels[1].contact, "74118 16122");



     strcpy(places_info[7].hotels[2].name, "SKD COMFORTS");
    places_info[7].hotels[2].price = 1600.0;
    places_info[7].hotels[2].distance = 1.5;
    places_info[7].hotels[2].rating = 3.6;
      strcpy(places_info[7].hotels[2].contact, "83648 50301");



        strcpy(places_info[8].place_name, "Unkal Lake");
    places_info[8].num_hotels = 3;

    strcpy(places_info[8].hotels[0].name, "THE PRESIDENT HOTEL");
    places_info[8].hotels[0].price = 4400.0;
    places_info[8].hotels[0].distance = 1.4;
    places_info[8].hotels[0].rating = 4.0;
      places_info[8].hotels[0].contact, "83622 34888";


     strcpy(places_info[8].hotels[1].name, "THE HANS HOTEL");
    places_info[8].hotels[1].price = 2700.0;
    places_info[8].hotels[1].distance = 3.0;
    places_info[8].hotels[1].rating = 3.5;
    places_info[8].hotels[1].contact, "83623 74771";


     strcpy(places_info[8].hotels[2].name, "SUNSHINE LODGE");
    places_info[8].hotels[2].price = 1500;
    places_info[8].hotels[2].distance = 2.7;
    places_info[8].hotels[2].rating = 2.5;
       places_info[8].hotels[2].contact, "79474 26286";



    strcpy(places_info[9].place_name, "ISKCON Sri Krishna Balaram Temple");
    places_info[9].num_hotels = 4;

    strcpy(places_info[9].hotels[0].name, "HOTEL SHRI KRISHNA BHAVAN");
    places_info[9].hotels[0].price = 700.0;
    places_info[9].hotels[0].distance = 12;
    places_info[9].hotels[0].rating = 3.5;
      places_info[9].hotels[0].contact, "79474 63610";


     strcpy(places_info[9].hotels[1].name, "THE PRESIDENT HOTEL");
    places_info[9].hotels[1].price = 4400.0;
    places_info[9].hotels[1].distance = 6.5;
    places_info[9].hotels[1].rating = 4.0;
      places_info[9].hotels[1].contact, "83622 34888";


     strcpy(places_info[9].hotels[2].name, "HOTEL TRAVEL INN");
    places_info[9].hotels[2].price = 2500.0;
    places_info[9].hotels[2].distance = 3.3;
    places_info[9].hotels[2].rating = 3.8;
    places_info[9].hotels[2].contact, "99005 33077";


     strcpy(places_info[9].hotels[3].name, "METROPOLIS HOTEL");
    places_info[9].hotels[3].price = 1700.0;
    places_info[9].hotels[3].distance = 10;
    places_info[9].hotels[3].rating=4.0;
     places_info[9].hotels[3].contact, "83642 66666";


    strcpy(places_info[10].place_name, "NUGGIKERI HANUMAN TEMPLE");
    places_info[10].num_hotels = 3;

     strcpy(places_info[10].hotels[0].name, "SHIVRATN COMFORTS");
    places_info[10].hotels[0].price = 1600.0;
    places_info[10].hotels[0].distance = 8.0;
    places_info[10].hotels[0].rating = 3.0;
     places_info[10].hotels[0].contact, "86602 31347";


     strcpy(places_info[10].hotels[1].name, "HOTEL CROWN INN");
    places_info[10].hotels[1].price = 1500.0;
    places_info[10].hotels[1].distance = 8.8;
    places_info[10].hotels[1].rating = 3.5;
     places_info[10].hotels[1].contact, "89042 64777";


     strcpy(places_info[10].hotels[2].name, "HOTEL MANDHAR");
    places_info[10].hotels[2].price = 1800;
    places_info[10].hotels[2].distance = 8.3;
    places_info[10].hotels[2].rating=3.0;
     places_info[9].hotels[1].contact, "95389 24411";


}   // Initialize details for the second place


// Funtion To print Path in Dijkstra algorithm
void printPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf(" -> %s", places[j]);
}

// Function To Display Shortest distance from source to destination.
void displayDistance(int dist[], int parent[], int src, int dest, float graph[NUM_PLACES][NUM_PLACES])
 {
    printf("Shortest distance from %s to %s is: %d km\n", places[src], places[dest], dist[dest]);

    int speed = 35; // Average speed in km/h
    double time = (double)dist[dest] / speed; // Time in hours

    printf("Approximate time taken: %.2f hours\n\n", time);

    printf("Path: %s", places[src]);
    //printf("\n");
    printPath(parent, dest);
    //printf("\n\n%s\n\n", descriptions[dest]);

    // Display hotels if user asks
    askHotels(dest);

}

// This Function Asks User Whether do you want to see hotels and lodges nearer to this destination.
void askHotels(int dest)
{
      char choice;
    printf("\n");
    printf("\nWould you like to see hotels and lodges for this destination? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
        displayHotels(dest);
        displaySortedHotels(dest);
        displaySortedHotels(dest);
    }
}


// It calculates the minimum Distance From The given Graph.

int minDistance(int dist[], bool visited[])
{
    int min = INF, min_index;
    for (int v = 0; v < NUM_PLACES; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}


//Find The minimum Distance from Source To destination
// and print the shortest path.

void dijkstra(float graph[NUM_PLACES][NUM_PLACES], int src, int dest)
{
    int dist[NUM_PLACES], parent[NUM_PLACES];
    bool visited[NUM_PLACES];

    for (int i = 0; i < NUM_PLACES; i++)
    {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < NUM_PLACES - 1; count++)
    {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < NUM_PLACES; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printf("\nDestination: %s\n", places[dest]);
    printf("Description: %s\n\n", descriptions[dest]);

    displayDistance(dist, parent, src, dest, graph);
}

// Function that takes pattern as a input place name and matches with place list
// then displays distances from that place to all places.

int boyer_moore_search(const char *pattern, const char *text)
{
    int m = strlen(pattern);
    int n = strlen(text);

    int bad_char[256];
    for (int i = 0; i < 256; i++)
    {
        bad_char[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
          bad_char[(unsigned char)pattern[i]] = i;
    }

    int s = 0;
    while (s <= n - m)
    {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j])
        {
             j--;
        }
        if (j < 0)
        {
             return s; // pattern found
        }
        s += (j - bad_char[(unsigned char)text[s + j]]);
    }

    return -1; // pattern not found
}

int get_vertex_index(const char *vertex_name)
{
    for (int i = 0; i < NUM_PLACES; i++)
    {
        if (boyer_moore_search(vertex_name, places[i]) != -1)
        {
            return i;
        }
    }
    return -1; // Vertex not found
}

// Function takes a string which returned by the booyer mOore algorithm
// it displays the distances from that source to destination.

void bellman_ford(const char *start_vertex)
{

    float graph[NUM_PLACES][NUM_PLACES] =
    {
        // Fill in the distances between places in Hubli city
        // For direct paths, put 0, for unconnected places, put INF or a high value
        {0, 16,16, 16.5, 16, 19, 20, 20, 22, 26,32},
        {16, 0, 0.65, 1, 3.2, 3.5, 4.7, 4.4, 6.5, 11, 21},
        {16, 0.65, 0, 0.5, 3.3, 3.1, 4.2, 3.9, 6, 10, 19},
        {16.5, 1, 0.5, 0, 3.4, 2.6, 4.3, 3.4, 5.5, 9.6, 19.2},
        {16, 3.2, 3.3, 3.4, 0, 2.6, 6.8, 6.1, 8.2, 12, 19.4},
        {19, 3.5, 3.1, 2.6, 2.7, 0, 5.7, 4.5, 5.9, 10, 16},
        {20, 4.7, 4.2, 4.3, 6.8, 5.7, 0, 3.5, 4.8, 8.9, 22},
        {20, 4.4, 3.9, 3.4, 6.1, 4.5, 3.5, 0, 2.4, 6.6, 19},
        {22, 6.5, 6, 5.5, 8.2, 5.9, 4.8, 2.4, 0, 5.3, 18},
        {26, 11, 10, 9.6, 12, 10, 8.9, 6.6, 5.3, 0, 13},
        {32, 21, 19, 19.2, 19.4, 16, 22, 19, 18, 13, 0}
    };
    int start_index = get_vertex_index(start_vertex);

    if (start_index == -1)
    {
        printf("Invalid starting vertex\n");
        return;
    }

    float dist[NUM_PLACES];
    int pred[NUM_PLACES];

    // Initialization
    for (int i = 0; i < NUM_PLACES; i++)
    {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[start_index] = 0;

    // Relaxation
    for (int k = 0; k < NUM_PLACES - 1; k++)
    {
        for (int i = 0; i < NUM_PLACES; i++)
        {
            for (int j = 0; j < NUM_PLACES; j++)
            {
                if (dist[i] + graph[i][j] < dist[j])
                {
                    dist[j] = dist[i] + graph[i][j];
                    pred[j] = i;
                }
            }
        }
    }

    // Check for negative cycles
    for (int i = 0; i < NUM_PLACES; i++)
    {
        for (int j = 0; j < NUM_PLACES; j++)
        {
            if (dist[i] + graph[i][j] < dist[j])
            {
                printf("Negative cycle detected, Bellman-Ford algorithm not applicable.\n");
                return;
            }
        }
    }

    // Print the shortest paths
    printf("\n");
    printf("\nShortest Paths from %s:\n", places[start_index]);
    for (int i = 0; i < NUM_PLACES; i++)
    {
        if (i != start_index)
        {
            printf("%s to %s: Distance %.2f\n", places[start_index], places[i], dist[i]);
        }
    }
}


// kruskals algo
// Define a structure to represent an edge in the graph
typedef struct
{
    int src, dest;
    float weight;
} Edge;


// Define a structure to represent a subset for Union-Find
typedef struct
{
    int parent;
    int rank;  // Add rank information
} Subset;

// Global variables to store the result (minimum spanning tree)
Edge result[NUM_PLACES - 1];
Subset subsets[NUM_PLACES];


// Find set of an element (with path compression)
int find(int i)
{
    if (subsets[i].parent != i)
    {
           subsets[i].parent = find(subsets[i].parent);
    }
    return subsets[i].parent;
}


// Perform union of two sets (with union by rank)
void unionSets(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY)
    {
        if (subsets[rootX].rank < subsets[rootY].rank)
            subsets[rootX].parent = rootY;
        else if (subsets[rootX].rank > subsets[rootY].rank)
            subsets[rootY].parent = rootX;
        else
        {
            subsets[rootY].parent = rootX;
            subsets[rootX].rank++;
        }
    }
}

//Buble sort algorithm to sort edges in kruskal algorithm.
void bubbleSortEdges(Edge edges[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                // Swap edges[j] and edges[j+1]
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}
// Kruskal's algorithm to find the minimum spanning tree
void kruskalMST(float graph[NUM_PLACES][NUM_PLACES])
{
    // Initialize subsets
    for (int i = 0; i < NUM_PLACES; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Sort all edges in non-decreasing order of their weight
    Edge edges[NUM_PLACES * NUM_PLACES];
    int edgeCount = 0;

    for (int i = 0; i < NUM_PLACES; i++)
        {
        for (int j = i + 1; j < NUM_PLACES; j++)
        {
            if (graph[i][j] != 0)
            {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

 bubbleSortEdges(edges, edgeCount);

    // Process each edge in sorted order
    int e = 0;  // Index variable for sorted edges
    int i = 0;  // Index variable for result[]

    while (i < NUM_PLACES - 1 && e < edgeCount)
        {
        Edge nextEdge = edges[e++];

        int x = find(nextEdge.src);
        int y = find(nextEdge.dest);

        if (x != y)
        {
            result[i++] = nextEdge;
            unionSets(x, y);
        }
    }
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < NUM_PLACES - 1; i++)
    {
        printf("Edge: %d - %d\n", result[i].src, result[i].dest);
    }
}


void postLoginMenu()
{
    float graph[NUM_PLACES][NUM_PLACES] =
    {
        // Fill in the distances between places in Hubli city
        // For direct paths, put 0, for unconnected places, put INF or a high value
        {0, 16,16, 16.5, 16, 19, 20, 20, 22, 26,32},
        {16, 0, 0.65, 1, 3.2, 3.5, 4.7, 4.4, 6.5, 11, 21},
        {16, 0.65, 0, 0.5, 3.3, 3.1, 4.2, 3.9, 6, 10, 19},
        {16.5, 1, 0.5, 0, 3.4, 2.6, 4.3, 3.4, 5.5, 9.6, 19.2},
        {16, 3.2, 3.3, 3.4, 0, 2.6, 6.8, 6.1, 8.2, 12, 19.4},
        {19, 3.5, 3.1, 2.6, 2.7, 0, 5.7, 4.5, 5.9, 10, 16},
        {20, 4.7, 4.2, 4.3, 6.8, 5.7, 0, 3.5, 4.8, 8.9, 22},
        {20, 4.4, 3.9, 3.4, 6.1, 4.5, 3.5, 0, 2.4, 6.6, 19},
        {22, 6.5, 6, 5.5, 8.2, 5.9, 4.8, 2.4, 0, 5.3, 18},
        {26, 11, 10, 9.6, 12, 10, 8.9, 6.6, 5.3, 0, 13},
        {32, 21, 19, 19.2, 19.4, 16, 22, 19, 18, 13, 0}
    };

    initializeHotels();
 displayAllPlaces();

    int startVertex;

    // Ask user to enter the starting vertexprintf("\n");
    printf("\n");
    printf("\n");
    printf("Enter the starting point of your journey to see optimal path to cover all above places(0 to %d): ", NUM_PLACES);
    scanf("%d", &startVertex);

    if (startVertex < 0 || startVertex >= NUM_PLACES)
    {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    // Display the optimal path
    dfs(startVertex, NULL, NULL, 0);
    kruskalMST(graph);
    //printf("Welcome to Hubli City!\n");
printf("\n");

printf("\n");

    printf("Places:\n");
    for (int i = 0; i < NUM_PLACES; i++)
    {
        printf("%d. %s\n", i + 1, places[i]);
    }

char start_vertex[100];
     printf("\n");

    printf("Enter the starting Place name to see distance to all places : ");
    scanf("%s", start_vertex);

    bellman_ford(start_vertex);



printf("\n");
    printf("Places:\n");
    for (int i = 0; i < NUM_PLACES; i++)
    {
        printf("%d. %s\n", i + 1, places[i]);
    }

    int src, dest;
    printf("\nEnter source place index (1 to %d): ", NUM_PLACES);
    scanf("%d", &src);
    printf("Enter destination place index (1 to %d): ", NUM_PLACES);
    scanf("%d", &dest);

    src--; // Adjusting to array indexing (starting from 0)
    dest--; // Adjusting to array indexing (starting from 0)

    if (src < 0 || src >= NUM_PLACES || dest < 0 || dest >= NUM_PLACES)
    {
        printf("Invalid input\n");
        return;
    }

    dijkstra(graph, src, dest);

    displaySortedHotels(dest);
    getUserHotelChoice(dest);
}

// it takes selected hotel as input and mathching with the already displaying hotel list.

int RobinKarp(const char *pattern, struct Hotel hotels[], int num_hotels)
{
    int patternLength = strlen(pattern);

    for (int i = 0; i < num_hotels; i++)
    {
        const char *hotelName = hotels[i].name;
        int hotelNameLength = strlen(hotelName);

        if (hotelNameLength >= patternLength)
        {
            int j;
            for (j = 0; j < patternLength; j++)
            {
                if (hotelName[j] != pattern[j])
                {
                    break;
                }
            }

            if (j == patternLength)
            {
                // Pattern found in hotel name
                return i;
            }
        }
    }

    // Pattern not found in any hotel name
    return -1;
}


//For calculating the customer bill by taking number of days they want to spend
//and total amount of their order then apply 18% GST then giving 25% discount;
void calculateBill(struct Hotel selectedHotel,double totalAmount)
{

        int checkoutDay;
    printf("Enter your checkout day (1 for today, 2 for tomorrow, and so on): ");
    scanf("%d", &checkoutDay);

    // Calculate the total amount based on the checkout day
    double rentAmount = selectedHotel.price * checkoutDay;

    // Display the total amount
    printf("\n");
    double finalAmount=0;

     printf(BLUE_TEXT "CheckOut Summary\n" RESET_TEXT);
    printf("Hotel Rent Amount (for %d days): $%.2f\n", checkoutDay, rentAmount);
    printf("Items Bill: $%.2f\n", totalAmount);
    finalAmount=rentAmount + totalAmount;
    printf("Total Amount: $%.2f\n", finalAmount);

    finalAmount=finalAmount*0.18+finalAmount;
    printf("After Taxation of 'SGST:9 percent' and 'CGST:9 percent' Your Total amount:$%.2f\n",finalAmount);
    finalAmount=finalAmount-finalAmount*0.25;
    printf("Hence you are the new customer of the %s they are giving '25 percent' discount\n",selectedHotel.name);
    printf("So,Final Total Amount To be paid is $%.2f\n",finalAmount);


}

// FUntion which performs operations which should be execute after checkout.
void afterCheckout(struct Hotel selectedHotel)
{

    printf("\n");
     printf(BLUE_TEXT "Thank you for visiting %s!" RESET_TEXT, selectedHotel);
     printf("\n");
     int ask;
     printf("Do You Want to Continue Your Aim Of Exploring HUBBLI(1 for yes/0 for no)");
     printf("\n");
     scanf("%d",&ask);
     if(ask==1)
     {
          postLoginMenu();
     }

     else
     {
         printf(YELLOW_TEXT "ThanksFor Visiting Hubbli\n", RESET_TEXT);
         printf("\n");
         printf(GREEN_TEXT "Thanks For Using Our Platform 'Budget Friendly Travel Planner'" RESET_TEXT);
         printf("\n");
         exit(0);
     }
}



void getUserHotelChoice(int dest) {
       char choiceHotel[100];
    printf("\nEnter the name of the hotel you want to select: ");
    scanf("%s", choiceHotel);

    // Use Rabin-Karp algorithm to find the hotel in the list
    int hotelIndex = RobinKarp(choiceHotel, places_info[dest].hotels, places_info[dest].num_hotels);

    if (hotelIndex == -1)
    {
        printf("Hotel not found!\n");
        return;
    }

    struct Hotel selectedHotel = places_info[dest].hotels[hotelIndex];

    // Print information about the selected hotel
    printf("\nYou have selected: %s - Price: %.2f - Distance: %.2f km - Rating: %d/5\n", selectedHotel.name,
           selectedHotel.price, selectedHotel.distance, selectedHotel.rating);
    printf("\n");
    char helpChoice;
    printf("Do you Want To Order Anything? (y/n): ");
    scanf(" %c", &helpChoice);
    printf("\n");
    if (helpChoice == 'y' || helpChoice == 'Y')
    {
            printf("\n");
        printf(YELLOW_TEXT "Hotel Contact Number: %s\n" RESET_TEXT, selectedHotel.contact);
    }

    int itemChoice;
    double totalAmount = 0.0;

    struct TreeNode *root = NULL;

struct MenuItem commonMenu[] =
{
    // Soups
    {"Tomato Soup", 100.0},
    {"Veg Clear Soup", 130.0},
    {"Veg Manchow Soup", 130.0},
    {"Sweet Corn Soup", 130.0},
    {"Chicken Hot and Sour Soup", 140.0},
    {"Chicken Manchow Soup", 140.0},
    {"Chicken Sweet Corn Soup", 140.0},
    {"Chicken Lemon Soup", 140.0},

    // Starters
    {"Boiled Veg Butter", 150.0},
    {"Hara Bhara Kabab", 195.0},
    {"Tandoor Gobi", 250.0},
    {"Chicken Tikka", 360.0},
    {"Chicken Banjara", 360.0},
    {"Chicken Hariyali", 360.0},
    {"Chicken Lasooni Dhaniya Tikka", 380.0},
    {"Chicken Kalmi Kabab [Single]", 200.0},
    {"Chicken Tangdi Kabab [Single]", 280.0},
    {"Chicken Tandoori", 475.0},
    {"Mutton Coriander", 450.0},
    {"Mutton Seekh Kabab", 450.0},
    {"Pomfret (SEASONAL)", 800.0},
    {"Surmai (SEASONAL)", 700.0},
    {"Prawns (SEASONAL)", 750.0},

    // Chinese Veg Starters
    {"Gobi 65", 200.0},
    {"Gobi Chilli", 200.0},
    {"Gobi Manchurian", 200.0},
    {"Paneer 65", 210.0},
    {"Paneer Chilli", 210.0},
    {"Paneer Manchurian", 210.0},
    {"Baby Corn 65", 210.0},
    {"Baby Corn Chilli", 210.0},
    {"Baby Corn Manchurian", 210.0},
    {"Mushroom 65", 210.0},
    {"Mushroom Chilli", 210.0},
    {"Mushroom Manchurian", 210.0},

    // Chinese Non-Veg Starters
    {"Egg Chilli", 200.0},
    {"Egg Manchurian", 200.0},
    {"Chicken 65", 330.0},
    {"Chicken Manchurian", 330.0},
    {"Chicken Chilli", 330.0},
    {"Chicken Pepper", 330.0},
    {"Chicken Lollipop", 330.0},
    {"Chicken Satay", 360.0},
    {"Chicken Drumstick", 360.0},
    {"Mutton Chilli", 400.0},
    {"Mutton Pepper Dry", 400.0},

    // Main Course
    {"Veg Hyderabadi", 230.0},
    {"Veg Kolhapuri", 230.0},
    {"Veg Makhanwala", 230.0},
    {"Veg Handi", 230.0},
    {"Veg Peshawari", 240.0},
    {"Veg Kadai", 240.0},
    {"Veg Angari", 240.0},
    {"Mushroom Masala", 250.0},
    {"Methi Malai Matar", 265.0},
    {"Makai Palak", 265.0},
    {"Kaju Masala", 290.0},
    {"Kaju Korma", 290.0},
    {"Kaju Paneer", 290.0},
    {"Palak Paneer", 290.0},
    {"Paneer Butter", 290.0},
    {"Paneer Kolhapuri", 290.0},
    {"Paneer Kadai", 290.0},
    {"Paneer Tikka Masala", 310.0},

    // DAL
    {"Dal Fry", 195.0},
    {"Dal Tadka", 220.0},
    {"Dal Kolhapuri", 220.0},
    {"Dal Palak", 220.0},

    // Non-Veg Main Course
    {"Egg Kadai", 230.0},
    {"Egg Kolhapuri", 230.0},
    {"Egg Maharaja", 260.0},
    {"Egg Kachha Masala", 260.0},
    {"Murgh Kolhapuri", 280.0},
    {"Murgh Kali Mirchi", 300.0},
    {"Murgh Makhanwala", 300.0},
    {"Murgh Patiala", 300.0},
    {"Murgh Malwani", 300.0},
    {"Mutton Hyderabadi", 340.0},
    {"Mutton Kolhapuri", 340.0},
    {"Mutton Handi", 340.0},
    {"Mutton Rogan Josh", 370.0},
    {"Mutton Keema Masala", 370.0},
    {"Mutton Malwani", 370.0},

    // Chinese Veg Main Course
    {"Diced Veg in Hot Garlic Sauce", 230.0},
    {"Mushroom in Schezwan Sauce", 230.0},
    {"Veg Sweet N Sour Sauce", 230.0},

    // Chinese Non-Veg Main Course
    {"Chicken in Hot Garlic Sauce", 310.0},
    {"Chicken Schezwan Sauce", 310.0},
    {"Chicken Manchurian Sauce", 310.0},

    // Breads
    {"Roti", 40.0},
    {"Butter Roti", 50.0},
    {"Cheese Garlic Naan", 130.0},
    {"Butter Naan", 80.0},
    {"Butter Kulcha", 50.0},
    {"Aloo Paratha", 130.0},

    // Rice and Biryani
    {"Steamed Rice", 100.0},
    {"Jeera Rice", 195.0},
    {"Dal Khichdi", 195.0},
    {"Veg Pulao", 230.0},
    {"Paneer Pulao", 230.0},
    {"Veg Biryani", 260.0},
    {"Egg Biryani", 250.0},
    {"Chicken Biryani", 310.0},
    {"Mutton Biryani", 360.0},

    // Fried Rice and Noodles
    {"Egg Fried Rice", 200.0},
    {"Egg Schezwan Fried Rice", 250.0},
    {"Chicken Fried Rice", 250.0},
    {"Chicken Schezwan Fried Rice", 250.0},
    {"Veg Hakka Noodles", 195.0},
    {"Veg Schezwan Noodles", 220.0},
    {"American Chopsuey", 260.0},
    {"Veg Chowmein", 260.0},
    {"Chicken Hakka Noodles", 230.0},
    {"Chicken Schezwan Noodles", 230.0},
    {"Chicken American Chopsuey", 280.0},
    {"Chicken Chowmein", 280.0},
    {"Special Chicken Chilli Noodles", 380.0},

    // Snacks
    {"Corn Basket", 210.0},

    // Accompaniment
    {"Garden Green Salad", 100.0},

    // Drinks (Beverages)
    {"Mineral Water [1 litre]", 16.0},
};

    // Insert menu items into the binary search tree
    for (int i = 0; i < sizeof(commonMenu) / sizeof(commonMenu[0]); i++)
    {
        root = insertNode(root, commonMenu[i]);
    }

    // Display the menu using in-order traversal of the binary search tree
    printf("Menu:\n");
    int serialNumber=0;
    displayMenuBST(root,&serialNumber);

  for (int i = 0; i < sizeof(commonMenu) / sizeof(commonMenu[0]); i++)
  {
      insert(root,commonMenu[i]);
  }
  printf("\n");

     mostexpensiveMenuItem(root);

     printf("\n");
     leastexpensiveMenuItem(root);
     printf("\n");

    // Free memory
    freeTree(root);

    do {
        printf("Enter the number of the item you want to order (0 to exit): ");
       // printf("\n");
        scanf("%d", &itemChoice);

        if (itemChoice >= 1 && itemChoice <= sizeof(commonMenu) / sizeof(commonMenu[0]))
        {
            totalAmount += commonMenu[itemChoice - 1].price;
        } else if (itemChoice != 0)
        {
            printf("Invalid choice! Please enter a valid item number.\n");
        }

    } while (itemChoice != 0);

    printf("Total Amount of items you have ordered : $%.2f\n", totalAmount);

    calculateBill(selectedHotel,totalAmount);

    afterCheckout(selectedHotel);
}

int main() {
       srand((unsigned int)time(NULL));

    // Print the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working directory: %s\n", cwd);
    } else
    {
        perror("getcwd");
        exit(0);
    }
      struct User users[MAX_USERS];
    int userCount = 0;
    int choice;


    // Load existing user data from file
    FILE* file = fopen(FILENAME, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) == 2)
        {
            userCount++;
            if (userCount >= MAX_USERS)
            {
                break;
            }
        }
        fclose(file);
    }



printf(YELLOW_TEXT "Hearty Welcome To Our PlatForm Budget Friendly Travel Planer" RESET_TEXT);
 printf("\n");
    do {
        printf("\n1. Register\n2. Login\n3. LogOut\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                registerUser(users, &userCount);
                break;
            case 2:
                if (loginUser(users, userCount))
                {
                    printf(GREEN_TEXT "Login successful!\n" RESET_TEXT);
                    printf("\n");
                    postLoginMenu();  // Call the function for post-login functionality
                } else {
                    printf(RED_TEXT "Login failed. Invalid username or password." RESET_TEXT);
                    printf("\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.");
                printf("\n");
        }
    } while (choice != 3);

       file = fopen(FILENAME, "w");
    if (file != NULL)
    {
        for (int i = 0; i < userCount; i++)
        {
            fprintf(file, "%s %s\n", users[i].username, users[i].password);
        }
        fclose(file);
    }

    return 0;
}
