#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifndef NO_WEBSERVER
#include <crow.h>
#endif

#include "stations.h"
#include "trains.h"
#include "destinations.h"

#define STATION_1 "Ketapang (1)"
#define STATION_2 "Geurugok (2)"
#define STATION_3 "Pangkajene (3)"
#define STATION_4 "Patukan (4)"
#define STATION_5 "Binjai (5)"

#define TRAIN_A "Ambarawa Ekspres"
#define TRAIN_B "Tawang Alun"

#define SERVER_PORT 3000

stations_t stations;
trains_t trains;

std::string __read_string()
{
    std::string str;
    std::cin.ignore();
    getline(std::cin, str, '\n');
    return str;
}

void railwayn_insert_default_data() 
{
    trains_insert_last(trains, {TRAIN_A});
    trains_insert_last(trains, {TRAIN_B});

    stations_elm_t *station_1 = stations_insert_last(stations, {STATION_1});
    stations_elm_t *station_2 = stations_insert_last(stations, {STATION_2});
    stations_elm_t *station_3 = stations_insert_last(stations, {STATION_3});
    stations_elm_t *station_4 = stations_insert_last(stations, {STATION_4});
    stations_elm_t *station_5 = stations_insert_last(stations, {STATION_5});

    stations_add_ticket(station_1, 40, station_2);
    stations_add_ticket(station_1, 20, station_3);
    stations_add_ticket(station_1, 50, station_3);

    stations_add_ticket(station_2, 40, station_3);
    stations_add_ticket(station_2, 40, station_4);
    stations_add_ticket(station_2, 50, station_5);

    stations_add_ticket(station_3, 40, station_1);
    stations_add_ticket(station_3, 30, station_4);
    stations_add_ticket(station_3, 20, station_5);

    stations_add_ticket(station_4, 40, station_5);

    stations_add_ticket(station_5, 10, station_1);
    stations_add_ticket(station_5, 10, station_2);
}

void menu() {
    int option;

    do {
        std::cout << "------------------------------------" << std::endl;
        std::cout << "      RAILWAYN - UNI ASSIGNMENT     " << std::endl;
        std::cout << "        INTERACTIVE MAIN MENU       " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "1. Insert train" << std::endl;
        std::cout << "2. Show all trains" << std::endl;
        std::cout << "3. Delete train" << std::endl;
        std::cout << "4. Search train" << std::endl;
        std::cout << "5. Search station" << std::endl;
        std::cout << "6. Insert station" << std::endl;
        std::cout << "7. Assign ticket to train" << std::endl;
        std::cout << "8. Show all trains with tickets" << std::endl;
        std::cout << "9. Search ticket within train" << std::endl;
        std::cout << "10. Delete stations from train (?)" << std::endl;
        std::cout << "11. Count tickets within train"<< std::endl;
        std::cout << "12. Load pre-defined data [SP]"<< std::endl;
        std::cout << "13. Simulate train run [SP]"<< std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> option;

        switch (option)
        {
        case 1: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();
            trains_insert_last(trains, {train_name});
            std::cout << "[INFO] Successfully added train" << std::endl;
            break;
        }
        case 2: {
            trains_debug(trains, false);
            break;
        }
        case 3: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();
            trains_delete(trains, trains_find(trains, train_name));
            std::cout << "[INFO] Successfully deleted train" << std::endl;
            break;
        }
        case 4: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();
            trains_elm_t *train = trains_find(trains, train_name);

            if (train == NULL) {
                std::cout << "[INFO] Train not found" << std::endl;
                break;
            }

            std::cout << "[INFO] Train found" << std::endl;
            break;
        }
        case 5: {
            std::cout << "Station name ::= ";
            std::string station_name = __read_string();
            stations_elm_t *station = stations_find(stations, station_name);

            if (station == NULL) {
                std::cout << "[INFO] Station not found" << std::endl;
                break;
            }

            std::cout << "[INFO] Station found:" << std::endl;
            std::cout << "    - Name: " << station->info.name << std::endl;

            for (auto it = station->info.tickets.begin(); it != station->info.tickets.end(); it++) {
                std::cout << "        - Passengers: " <<  it->passengers << std::endl;
                std::cout << "        - Dest: " <<  it->dest->info.name << std::endl;
                std::cout << std::endl;
            }

            break;
        }
        case 6: {
            std::cout << "Station name ::= ";
            std::string station_name = __read_string();
            stations_elm_t *station = stations_insert_last(stations, {station_name});
            std::cout << "[INFO] Successfully added station" << std::endl;
            break;
        }
        case 7: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();
            trains_elm_t *train = trains_find(trains, train_name);

            std::cout << "Ticket destination station name ::= ";
            std::string station_name = __read_string();
            stations_elm_t *station = stations_find(stations, station_name);

            std::cout << "Ticket passengers count ::= ";
            size_t passengers = 0;
            std::cin >> passengers;

            stations_elm_t *dest = stations_find(stations, station_name);

            destinations_insert_first(train->destinations, { passengers, station });
            std::cout << "[INFO] Successfully added ticket" << std::endl;
            break;
        }
        case 8: {
            trains_debug(trains, true);
            break;
        }
        case 9: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();
            trains_elm_t *train = trains_find(trains, train_name);

            std::cout << "Station name ::= ";
            std::string station_name = __read_string();

            stations_elm_t *station = trains_find_station_dest(train, station_name);

            if (station == NULL) {
                std::cout << "[INFO] No destination found" << std::endl;
                break;
            }

            std::cout << "[INFO] Train has destination" << std::endl;
            break;
        }
        case 10: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();

            std::cout << "Station name ::= ";
            std::string station_name = __read_string();

            __trains_delete_station_entirely(trains, stations, trains_find(trains, train_name), station_name);
            std::cout << "[INFO] Successfully deleted train with stations" << std::endl;
            break;
        }
        case 11: {
            std::cout << "Train name ::= ";
            std::string train_name = __read_string();

            std::cout << "[INFO] " << destinations_length(trains_find(trains, train_name)->destinations) << " tickets found" << std::endl;
            break;
        }
        case 12: {
            trains_cleanup(trains);
            stations_cleanup(stations);

            trains_create(trains);
            stations_create(stations);

            railwayn_insert_default_data();
            std::cout << "[INFO] Successfully loaded data" << std::endl;
            break;
        }
        case 13: {
            std::cout << "[INFO] Simulating Run.." << std::endl;
            trains_simulate_run(trains, stations);
            break;
        }
        case 0: break;
        default:
            std::cout << "[ERR] Invalid option!" << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (option != 0);
}

#ifndef NO_WEBSERVER
void railwayn_start_server()
{
    crow::SimpleApp sv;

    CROW_ROUTE(sv, "/css/<string>")([](std::string filename) {
        crow::response res;
        res.set_static_file_info("./css/" + filename);
        return res;
    });

    CROW_ROUTE(sv, "/quit")([&]() {
        /* Trying to stop the server before 
         * returning the response considered harmful
         */
        sv.stop();

        return
            "<!DOCTYPE html>"
            "<html>"
                "<head>"
                    "<title>Railwayn</title>"
                    "<link rel=\"stylesheet\" href=\"/css/global.css\">"
                "</head>"
                "<body>"
                    "<main>"
                        "<h1>"
                            "<a href=\"/\">Railwayn</a>"
                        "</h1>"
                        "<p>Shutting down server..</p>"
                    "</main>"
                "</body>"
            "</html>";
    });

    CROW_ROUTE(sv, "/")([](const crow::request &req) {
        const char *reset = req.url_params.get("r");

        if (reset) {
            trains_cleanup(trains);
            stations_cleanup(stations);

            trains_create(trains);
            stations_create(stations);
        }

        std::stringstream html5;
        html5 <<
            "<!DOCTYPE html>"
            "<html>"
                "<head>"
                    "<title>Railwayn</title>"
                    "<link rel=\"stylesheet\" href=\"/css/global.css\">"
                "</head>"
                "<body>"
                    "<main>"
                        "<h1>"
                            "<a href=\"/\">Railwayn</a>"
                        "</h1>"
                        "<a href=\"/add/train\">"
                            "<button>"
                                "Add new train"
                            "</button>"
                        "</a>"
                        "<a href=\"/add/station\">"
                            "<button>"
                                "Add new station"
                            "</button>"
                        "</a>"
                        "<a href=\"/add/ticket\">"
                            "<button>"
                                "Add new ticket"
                            "</button>"
                        "</a>"
                        "<a href=\"/?r=1\">"
                            "<button>"
                                "Reset data"
                            "</button>"
                        "</a>"
                        "<a href=\"/quit\">"
                            "<button>"
                                "Quit"
                            "</button>"
                        "</a>"
                        "<p>Trains:</p>"
                        << trains_print_html5(trains) <<
                        "<p>Stations:</p>"
                        << stations_print_html5(stations) <<
                    "</main>"
                "</body>"
            "</html>";

        return html5.str();
    });

    CROW_ROUTE(sv, "/add/station")([](const crow::request &req) {
        const char *station_name = req.url_params.get("name");

        if (station_name && std::string(station_name) != "") {
            stations_insert_last(stations, {station_name});
        }

        std::stringstream html5;
        html5 <<
            "<!DOCTYPE html>"
            "<html>"
                "<head>"
                    "<title>Railwayn</title>"
                    "<link rel=\"stylesheet\" href=\"/css/global.css\">"
                "</head>"
                "<body>"
                    "<main>"
                        "<h1>"
                            "<a href=\"/\">Railwayn</a>"
                        "</h1>"
                        "<form action=\"/add/station\" method=\"GET\">"
                            "<div>"
                                "<label for=\"name\">Station name: </label>"
                                "<input name=\"name\" />"
                            "</div>"
                            "<button type=\"submit\">"
                                "Add"
                            "</button>"
                        "</form>"
                        "<p>Stations:</p>"
                        << stations_print_html5(stations) <<
                    "</main>"
                "</body>"
            "</html>";

        return html5.str();
    });

    CROW_ROUTE(sv, "/add/train")([](const crow::request &req) {
        const char *train_name = req.url_params.get("name");

        if (train_name && std::string(train_name) != "") {
            trains_insert_last(trains, {train_name});
        }

        std::stringstream html5;
        html5 <<
            "<!DOCTYPE html>"
            "<html>"
                "<head>"
                    "<title>Railwayn</title>"
                    "<link rel=\"stylesheet\" href=\"/css/global.css\">"
                "</head>"
                "<body>"
                    "<main>"
                        "<h1>"
                            "<a href=\"/\">Railwayn</a>"
                        "</h1>"
                        "<form action=\"/add/train\" method=\"GET\">"
                            "<div>"
                                "<label for=\"name\">Train name: </label>"
                                "<input name=\"name\" />"
                            "</div>"
                            "<button type=\"submit\">"
                                "Add"
                            "</button>"
                        "</form>"
                        "<p>Trains:</p>"
                        << trains_print_html5(trains) <<
                    "</main>"
                "</body>"
            "</html>";

        return html5.str();
    });

        std::cout << "7. Assign ticket to train" << std::endl;

    CROW_ROUTE(sv, "/add/ticket")([](const crow::request &req) {
        const char *origin_station = req.url_params.get("origin");
        const char *dest_station = req.url_params.get("dest");
        const char *passengers = req.url_params.get("passengers");

        if (origin_station && dest_station && passengers) {
            stations_elm_t *__origin = stations_find(stations, origin_station);
            stations_elm_t *__dest = stations_find(stations, dest_station);
            
            if (__origin && __dest) {
                stations_add_ticket(__origin, std::stoi(passengers), __dest);
            }
        }

        std::stringstream html5;
        html5 <<
            "<!DOCTYPE html>"
            "<html>"
                "<head>"
                    "<title>Railwayn</title>"
                    "<link rel=\"stylesheet\" href=\"/css/global.css\">"
                "</head>"
                "<body>"
                    "<main>"
                        "<h1>"
                            "<a href=\"/\">Railwayn</a>"
                        "</h1>"
                        "<form action=\"/add/ticket\" method=\"GET\">"
                            "<div>"
                                "<label for=\"origin\">Origin station: </label>"
                                "<input name=\"origin\" />"
                            "</div>"
                            "<div>"
                                "<label for=\"dest\">Destination station: </label>"
                                "<input name=\"dest\" />"
                            "</div>"
                            "<div>"
                                "<label for=\"passengers\">Passengers: </label>"
                                "<input name=\"passengers\" />"
                            "</div>"
                            "<button type=\"submit\">"
                                "Add"
                            "</button>"
                        "</form>"
                        "<p>Stations:</p>"
                        << stations_print_html5(stations) <<
                    "</main>"
                "</body>"
            "</html>";

        return html5.str();
    });

    sv.port(SERVER_PORT).multithreaded().run();
}
#endif // NO_WEBSERVER

/* 3. 12 */
int main(int argc, char **argv)
{
    trains_create(trains);
    stations_create(stations);

    std::string arg = argc >= 2 ? std::string(argv[1]) : "";

    if (argc >= 2 && (arg == "-h" || arg == "--help")) {
        std::cout << "Usage: " << argv[0] << " [-h | --help] [-R | --run] [-S | --serve]" << std::endl;
        std::cout << "An archive of a uni project." << std::endl;
        goto cleanups;
    }

    if (argc >= 2 && (arg == "-R" || arg == "--run")) {
        railwayn_insert_default_data();
        trains_simulate_run(trains, stations);
        goto cleanups;
    }

#ifndef NO_WEBSERVER
    if (argc >= 2 && (arg == "-S" || arg == "--serve")) {
        railwayn_start_server();
        goto cleanups;
    }
#endif // NO_WEBSERVER

    menu();

cleanups:
    trains_cleanup(trains);
    stations_cleanup(stations);
    return 0;
}
