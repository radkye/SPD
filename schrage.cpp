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
  int k = 0;
  int cmax = 0;
  int sprawdzenie = 0;
  std::vector<Task> permutations;

  while(!underPreparationTasks.empty() || !readyTasks.empty())
    {
      while(!underPreparationTasks.empty() && (underPreparationTasks.top().availabilityTerm <= t))
	{
	  Task zadanie = underPreparationTasks.top();
	  readyTasks.push(zadanie);
	  underPreparationTasks.pop();
	}
      if(readyTasks.empty())
	t = underPreparationTasks.top().availabilityTerm;
      else 
	{       
	  Task zadanie = readyTasks.top();
	  readyTasks.pop();
	  k = k + 1;
	  t = t + zadanie.estimatedTime;
	  permutations.push_back(zadanie);
	  cmax = std::max(cmax, t + zadanie.deliveryTime);
	}
    }
  
  std::cout << "Wynik: " << cmax << std::endl;
}
