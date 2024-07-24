class Object{
    public:
        float position[3] = {0.0f,0.0f,0.0f};
        float rotation[3] = {0.0f,0.0f,0.0f};
        float scale[3] = {1.0f,1.0f,1.0f};
        Model* model;
        bool enabled = true;
        Object(){}
        void draw(){
            if(true){
                GRRLIB_ObjectView(
                    this->position[0],this->position[2],this->position[2],
                    this->rotation[0],this->rotation[2],this->rotation[2],
                    this->scale[0],this->scale[2],this->scale[2]
                );
                this->model->draw();
            }
        }
        void translate(float x, float y, float z){
            this->position[0]+=x;
            this->position[1]+=y;
            this->position[2]+=z;
        }
        void rotate(float x, float y, float z){
            this->rotation[0]+=x;
            this->rotation[1]+=y;
            this->rotation[2]+=z;
        }
        void inflate(float x, float y, float z){
            this->scale[0]+=x;
            this->scale[1]+=y;
            this->scale[2]+=z;
        }
        void setPosition(float x, float y, float z){
            this->position[0]=x;
            this->position[1]=y;
            this->position[2]=z;
        }
        void setRotation(float x, float y, float z){
            this->rotation[0]=x;
            this->rotation[1]=y;
            this->rotation[2]=z;
        }
        void setScale(float x, float y, float z){
            this->scale[0]=x;
            this->scale[1]=y;
            this->scale[2]=z;
        }
        ~Object(){}
};