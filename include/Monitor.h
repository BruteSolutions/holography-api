#ifndef MONITOR_H_
#define MONITOR_H_


/**
 * Monitor class.
 */
class Monitor
{
  public:
    Monitor();
    ~Monitor();
    void display(Scene scn);
    void addShader(Shader s);
    std::vector<Shader> getShaders();

  private:
    unsigned int bufferSize;
    std::vector<Shader> shaders;
    Projector * proj;
};

#endif
