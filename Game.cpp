#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;
using std::cout;
using std::endl;

class Player{
public:
    string name;
    int health;
    int attack;
    int defence;
    int gold;
    int level;
    int xp;
    int potions;

    Player(string n)
    {
        name = n;
        health = 100;
        attack = 15;
        defence = 5;
        gold = 50;
        level = 1;
        xp = 0;
        potions = 3;
    }

    void showStats()
    {
        cout << "\n===== PLAYER STATS ====" << endl;
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defence: " << defence << endl;
        cout << "Gold: " << gold << endl;
        cout << "Level: " << level << endl;
        cout << "XP: " << xp << endl;
        cout << "Potions: " << potions << endl;
        cout << "======================\n" << endl;
    }

    void heal()
    {
        if (potions > 0)
        {
            potions--;
            health += 30;

            if (health > 100)
                health = 100;

            cout << "You used a potion! +30 HP" << endl;
        }
        else
        {
            cout << "No potions left!" << endl;
        }
    }

    void gainXP(int amount)
    {
        xp += amount;

        if (xp >= level * 50)
        {
            xp = 0;
            level++;
            attack += 5;
            defence += 2;
            health = 100;

            cout << "\nLEVEL UP!" << endl;
            cout << "You are now level" << level << endl;
        }
    }
};

class Enemy
{
public:
    string name;
    int health;
    int attack;

    Enemy(string n, int h, int a)
    {
        name = n;
        health = h;
        attack = a;
    }
};

void slowText(string text)
{
    for (char c : text)
    {
        cout << c;
        Sleep(20);
    }
    cout << endl;
}

void battle(Player &player, Enemy enemy)
{
    slowText("\nA wild " + enemy.name + "appears!");

    while (enemy.health > 0 && player.health > 0)
    {
        cout << "\nYour HP: " << player.health << " | " << enemy.name << " HP: " << enemy.health << endl;
        cout << "\n1. Attack" << endl;
        cout << "2. Use Potion" << endl;
        cout << "3. Run" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int damage = player.attack - (rand() % 5);
            enemy.health -= damage;

            cout << "You hit the" << enemy.name << "for " << damage << "damage!" << endl;

            if (enemy.health <= 0)
            {
                cout << "\nYou defeated the " << enemy.name << "!" << endl;
                player.gold += 20;
                player.gainXP(20);
                break;
            }
        }
        else if (choice == 2)
        {
            player.heal();
        }
        else if (choice == 3)
        {
            cout << "You escaped!" << endl;
            return;
        }
        else
        {
            cout << "Invalid choice!" << endl;
            continue;
        }

        int enemyDamage = enemy.attack - player.defence;

        if (enemyDamage < 0)
            enemyDamage = 0;

        player.health -= enemyDamage;

        cout << enemy.name << " attacked you for " << enemyDamage << " damage!" << endl;
    }

    if (player.health <= 0)
    {
        cout << "\nGAME OVER" << endl;
    }
}

void shop(Player &player) {
    int choice;

    do{
        cout << "\n===== SHOP =====" << endl;
        cout << "Gold: " << player.gold << endl;
        cout << "1. Buy Potion (20 gold)" << endl;
        cout << "2. Upgrade Attack (50 gold)" << endl;
        cout << "3. Upgrade Defence (40 gold)" << endl;
        cout << "4. Exit Shop" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            if (player.gold >= 20)
            {
                player.gold -= 20;
                player.potions++;
                cout << "Potion purchased!" << endl;
            }else
            {
                cout << "Not enough gold!" << endl;
            }
            break;

        case 2:
            if (player.gold >= 50)
            {
                player.gold -= 50;
                player.attack += 5;
                cout << "Attack upgraded!" << endl;
            }
            else
            {
                cout << "Not enough gold!" << endl;
            }
            break;

        case 3:
            if (player.gold >= 40)
            {
                player.gold -= 40;
                player.defence += 3;
                cout << "Defence upgraded!" << endl;
            }
            else
            {
                cout << "Not enough gold!" << endl;
            }
            break;

        case 4:
            cout << "Leaving shop..." << endl;
            break;

        default:
            cout << "Invalid option!" << endl;
        }

    } while (choice != 4);
}

void forestEvent(Player &player)
{
    int randomEvent = rand() % 4;

    switch (randomEvent)
    {
    case 0:
        battle(player, Enemy("Goblin", 40, 10));
        break;

    case 1:
        battle(player, Enemy("Skeleton", 50, 12));
        break;

    case 2:
        cout << "\nYou found a treasure chest!" << endl;
        player.gold += 30;
        cout << "+30 Gold" << endl;
        break;

    case 3:
        cout << "\nYou found a hidden potion!" << endl;
        player.potions++;
        break;
    }
}

void dungeon(Player &player)
{
    slowText("\nYou entered the dark dungeon...");

    battle(player, Enemy("Dungeon Guard", 60, 15));

    if (player.health > 0)
    {
        battle(player, Enemy("Dark Knight", 80, 20));
    }

    if (player.health > 0)
    {
        cout << "\nYou cleared the dungeon!" << endl;
        player.gold += 100;
        player.gainXP(50);
    }
}

void arena(Player &player)
{
    slowText("\nWelcome to the battle arena!");

    vector<Enemy> enemies;

    enemies.push_back(Enemy("Warrior", 45, 10));
    enemies.push_back(Enemy("Assassin", 55, 14));
    enemies.push_back(Enemy("Champion", 70, 18));

    for (int i = 0; i < enemies.size(); i++)
    {
        if (player.health > 0)
        {
            battle(player, enemies[i]);
        }
    }

    if (player.health > 0)
    {
        cout << "\nYou became the Arena Champion!" << endl;
        player.gold += 150;
    }
}

int main()
{
    srand(time(0));

    string playerName;

    cout << "===============================" << endl;
    cout << " SURVIVAL ADVENTURE GAME " << endl;
    cout << "===============================\n"
         << endl;

    cout << "Enter your player name: ";
    getline(cin, playerName);

    Player player(playerName);

    int choice;

    do
    {
        cout << "\n===== MAIN MENU =====" << endl;
        cout << "1. Explore Forest" << endl;
        cout << "2. Visit Shop" << endl;
        cout << "3. Enter Dungeon" << endl;
        cout << "4. Battle Arena" << endl;
        cout << "5. Show Stats" << endl;
        cout << "6. Rest" << endl;
        cout << "7. Exit Game" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            forestEvent(player);
            break;

        case 2:
            shop(player);
            break;

        case 3:
            dungeon(player);
            break;

        case 4:
            arena(player);
            break;

        case 5:
            player.showStats();
            break;

        case 6:
            cout << "\nYou rested and recovered health." << endl;
            player.health = 100;
            break;

        case 7:
            cout << "\nThanks for playing!" << endl;
            break;

        default:
            cout << "Invalid option!" << endl;
        }

        if (player.health <= 0)
        {
            cout << "\nYour adventure has ended..." << endl;
            break;
        }
    } while (choice != 7);

    return 0;
}
