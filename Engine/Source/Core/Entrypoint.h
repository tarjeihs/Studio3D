#pragma once

int main()
{
    auto Engine = new CEngine();
    
    Engine->Start();

    Engine->Run();

    Engine->Stop();

    delete Engine;

    return 0;
}