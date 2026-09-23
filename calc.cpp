#include <iostream>
using namespace std;

int main() {
    int speed, velocityX, velocityY, time, height, distance, acceleration, angle, choice;
    const int g = -9.80665;

    cout << "What do you want to calculate? \n1. Height\n2. Distance\n3. Time\n4. Angle\n";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Enter speed (m/s): ";
            cin >> speed;
            cout << "Enter angle (degrees): ";
            cin >> angle;
            velocityY = speed * sin(angle * 3.14159 / 180);
            height = (velocityY * velocityY) / (2 * g);
            cout << "Maximum height: " << height << " meters" << endl;
            break;
        case 2:
            cout << "Enter speed (m/s): ";
            cin >> speed;
            cout << "Enter angle (degrees): ";
            cin >> angle;
            velocityX = speed * cos(angle * 3.14159 / 180);
            time = (2 * speed * sin(angle * 3.14159 / 180)) / g;
            distance = velocityX * time;
            cout << "Distance traveled: " << distance << " meters" << endl;
            break;
        case 3:
            cout << "Enter speed (m/s): ";
            cin >> speed;
            cout << "Enter angle (degrees): ";
            cin >> angle;
            time = (2 * speed * sin(angle * 3.14159 / 180)) / g;
            cout << "Time of flight: " << time << " seconds" << endl;
            break;
        case 4:
            cout << "Enter speed (m/s): ";
            cin >> speed;
            cout << "Enter height (meters): ";
            cin >> height;
            angle = asin((height * g) / (speed * speed)) * (180 / 3.14159);
            cout << "Angle of projection: " << angle << " degrees" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }

    // cout << "Enter speed (m/s): ";
    // cin >> speed;
    // cout << "Enter angle (degrees): ";
    // cin >> angle;
    // velocityX = speed * cos(angle * 3.14159 / 180);
    // velocityY = speed * sin(angle * 3.14159 / 180);


    return 0;
}
