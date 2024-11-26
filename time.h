class Time
{

public:
	Time()
	{
		startTimeMilliseconds = getCurrentTimeInMillis();
	}

	long long getCurrentTimeInMillis()
	{

		return GetTickCount();
	}


	float deltaTime;
	long long startTimeMilliseconds = 0;
};
