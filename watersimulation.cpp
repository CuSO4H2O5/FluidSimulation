#include <cstdio>
#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class SimulationAllocator
{
public:
    static T* allocate(size_t _size)
    {
        return static_cast<T*>(_aligned_malloc(sizeof(T) * _size, 16));
    }
    
    static void deallocate(void* _ptr)
    {
        _aligned_free(_ptr);
    }
};

class WindSimulationScene
{
friend class WindSimulationSolver;
public:
    void initializeBuffer()
    {
        u = SimulationAllocator<float>::allocate(simulation_size + bound_size);
        v = SimulationAllocator<float>::allocate(simulation_size + bound_size);
        dense = SimulationAllocator<float>::allocate(simulation_size + bound_size);
    }

    void addEffect(int x, int y, int range, float* affected_buffer)
    {
        for( int i = 0; i < simulation_size + bound_size; i++)
        {
            for(int j = 0; j < simulation_size + bound_size; j++)
            {
                affected_buffer[IndexOf(i, j)] = std::pow((i - x), 2) + std::pow((j - y)
            }
        }
    }

    inline int IndexOf(int x, int y)
    {
        return x * (simulation_size + bound_size) + y;
    }
private:
    size_t simulation_size = 100;
    size_t bound_size = 1 * 2;
    float* u, v;
    float* dense;
};

class WindSimulationSolver
{
public:
    void solve()
    {
        diffuse();
    }
    void initialize(WindSimulationScene* scene)
    {
        _scene = scene;
    }
protected:
    void diffuse()
    {

    }
private:
    WindSimulationScene* _scene;
};


class WindSystemManager
{
public:
    void initialize()
    {
        _scene.initializeBuffer();
        _solver.initialize(&_scene);
    }

    void tick()
    {
        _solver.solve();
    }
    
    void draw(){
        _scene.draw();
    }
private:
    WindSimulationSolver _solver;
    WindSimulationScene _scene;
};


int main()
{
    WindSystemManager manager;
    manager.initialize();
    manager.tick();
    manager.draw();
}





