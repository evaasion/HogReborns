#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <enet/enet.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "enet.lib")

// Structure pour les fonctions réseau
struct NetworkFunctions {
    int(__stdcall* InitializeClient)(void);
    int(__stdcall* ConnectToServer)(const char*, int);
    int(__stdcall* SendData)(const char*);
    int(__stdcall* DisconnectFromServer)(void);
    void(__stdcall* CleanupClient)(void);
};

// Variables globales
ENetHost* client = nullptr;
ENetPeer* peer = nullptr;
bool isConnected = false;

// Fonction de logging
extern "C" __declspec(dllexport) void LogMessage(const char* message) {
    OutputDebugStringA((std::string("[HogReborns] ") + message + "\n").c_str());
}

// Fonctions réseau
int __stdcall InitializeClient(void) {
    LogMessage("Début InitializeClient");
    if (enet_initialize() != 0) {
        LogMessage("Échec de enet_initialize");
        return 0;
    }
    LogMessage("enet_initialize réussi");
    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client) {
        LogMessage("Échec de enet_host_create");
        enet_deinitialize();
        return 0;
    }
    LogMessage("enet_host_create réussi");
    return 1;
}

int __stdcall ConnectToServer(const char* ip, int port) {
    LogMessage("Tentative de connexion au serveur");
    if (!client) {
        LogMessage("Client non initialisé");
        return 0;
    }

    ENetAddress address;
    enet_address_set_host(&address, ip);
    address.port = static_cast<uint16_t>(port);

    peer = enet_host_connect(client, &address, 2, 0);
    if (!peer) {
        LogMessage("Échec de création du peer");
        return 0;
    }

    LogMessage("En attente de connexion...");
    ENetEvent event;
    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT) {
        isConnected = true;
        LogMessage("Connexion réussie");
        return 1;
    }

    LogMessage("Timeout de connexion");
    enet_peer_reset(peer);
    return 0;
}

int __stdcall SendData(const char* data) {
    if (!peer || !isConnected) {
        LogMessage("Impossible d'envoyer les données: non connecté");
        return 0;
    }

    ENetPacket* packet = enet_packet_create(data,
        strlen(data) + 1,
        ENET_PACKET_FLAG_RELIABLE);
    if (!packet) {
        LogMessage("Échec de création du packet");
        return 0;
    }

    if (enet_peer_send(peer, 0, packet) < 0) {
        LogMessage("Échec d'envoi du packet");
        enet_packet_destroy(packet);
        return 0;
    }

    return 1;
}

int __stdcall DisconnectFromServer(void) {
    if (!peer || !isConnected) {
        LogMessage("Déjà déconnecté");
        return 0;
    }

    LogMessage("Déconnexion...");
    enet_peer_disconnect(peer, 0);

    ENetEvent event;
    while (enet_host_service(client, &event, 3000) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            peer = nullptr;
            isConnected = false;
            LogMessage("Déconnexion réussie");
            return 1;
        }
    }

    enet_peer_reset(peer);
    peer = nullptr;
    isConnected = false;
    LogMessage("Déconnexion forcée");
    return 1;
}

void __stdcall CleanupClient(void) {
    LogMessage("Nettoyage...");
    if (isConnected) {
        DisconnectFromServer();
    }
    if (client) {
        enet_host_destroy(client);
        client = nullptr;
    }
    enet_deinitialize();
    LogMessage("Nettoyage terminé");
}

// Fonction pour exporter la structure des fonctions
extern "C" __declspec(dllexport) NetworkFunctions* __stdcall GetNetworkFunctions(void) {
    static NetworkFunctions functions = {
        InitializeClient,
        ConnectToServer,
        SendData,
        DisconnectFromServer,
        CleanupClient
    };
    LogMessage("Fonctions réseau exportées");
    return &functions;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    return TRUE;
}