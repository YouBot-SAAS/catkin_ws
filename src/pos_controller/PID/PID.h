class PID
{
private: 
	float i;
	float kp, ki, kd;
	float ep;
public:
	float update(float e);
	void set_params(float kp, float ki, float kd);
};
