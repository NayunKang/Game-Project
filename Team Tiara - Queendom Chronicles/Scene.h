#pragma once

class Engine;

class Scene
{
    Engine* Instance;

protected:
    Engine& engine() { return *Instance; }
    const Engine& engine() const { return *Instance; }

public:
    Scene(Engine& game_engine) : Instance(&game_engine) {}

    virtual void Update() = 0;
    virtual void Draw() const = 0;

    virtual ~Scene() = default;
    Scene(const Scene& other) = default;
    Scene(Scene&& other) noexcept = default;
    Scene& operator=(const Scene& other) = default;
    Scene& operator=(Scene&& other) noexcept = default;
};