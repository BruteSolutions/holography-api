#ifndef MONITOR_H_
#define MONITOR_H_


class Monitor
{
  public:
    Monitor(int * pointer, unsigned int len);
    void display(Scene scn);
    void addShader(Shader s);
    std::vector<Shader> getShaders();
    int * getBuffer();
    int getBufferSize();

  private:
    unsigned int bufferSize;
    std::vector<Shader> shaders;
    std::map<unsigned int, GLuint> objectMap;
};

#endif
