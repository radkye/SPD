#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

class Task {
public:
  int availabilityTerm;
  int estimatedTime;
  int deliveryTime;
  
  Task() = default;
  ~Task() = default;
};


int main()
{
  auto taskDeliveryComparison = 
    [](Task &left, Task &right) { 
    return left.deliveryTime < right.deliveryTime; 
  };

  auto taskTermComparison = 
    [](Task &left, Task &right) { 
    return left.availabilityTerm > right.availabilityTerm;
  };

  std::priority_queue<Task, std::vector<Task>, decltype(taskDeliveryComparison)> readyTasks(taskDeliveryComparison);
  std::priority_queue<Task, std::vector<Task>, decltype(taskTermComparison)> underPreparationTasks(taskTermComparison);

  int tasksAmount;
  std::cin >> tasksAmount;

  for(Task task; std::cin >> task.availabilityTerm >> task.estimatedTime >> task.deliveryTime;)
    underPreparationTasks.push(task);

  int t = 0;
  int cmax = 0;
  Task l;

  while(!underPreparationTasks.empty() || !readyTasks.empty())
    {
      while(!underPreparationTasks.empty() && (underPreparationTasks.top().availabilityTerm <= t))
	{
	  Task zadanie = underPreparationTasks.top();
	  readyTasks.push(zadanie);
	  underPreparationTasks.pop();
          if(zadanie.deliveryTime > l.deliveryTime)
          {
            l.estimatedTime = t - zadanie.availabilityTerm;
            t = zadanie.availabilityTerm;
            if(l.estimatedTime > 0)
              readyTasks.push(l);
          }
	}
      if(readyTasks.empty())
	t = underPreparationTasks.top().availabilityTerm;
      else 
	{       
	  Task zadanie = readyTasks.top();
	  readyTasks.pop();
	  t = t + zadanie.estimatedTime;
	  cmax = std::max(cmax, t + zadanie.deliveryTime);
          l = zadanie;
	}
    }
  
  std::cout << "Wynik: " << cmax << std::endl;
}
