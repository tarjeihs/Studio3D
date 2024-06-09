#pragma once

extern CEngine* CreateEngine();

int main()
{
    auto Engine = CreateEngine();

    Engine->Start();

    Engine->Run();

    Engine->Stop();

    delete Engine;

    return 0;
}