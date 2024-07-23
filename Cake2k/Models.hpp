class Model{
    public:
    float rotation[3] = {0.0f,0.0f,0.0f};
    float position[3] = {0.0f,0.0f,0.0f};
    float scale[3] = {1.0f,1.0f,1.0f};
    Model(){/*no-op*/};
    void translate(float tPosition[3]){
        this->position[0] += tPosition[0];
        this->position[1] += tPosition[1];
        this->position[2] += tPosition[2];
    }
    void draw(){/*no-op*/}
};