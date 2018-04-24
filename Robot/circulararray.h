/// Circular Array
/// Easy running averages

#define TOTAL_VALUES  5

template <typename T>
class CircularArray
{
public:
  CircularArray();
  CircularArray(T minValue, T maxValue);

  T getAverage();
  void addValue(T value);

  void dumpArray();

private:
  T minimumValue;
  T maximumValue;
  unsigned char currentIndex;
  unsigned char usedIndexes;
  T values[TOTAL_VALUES];
};

template <typename T>
T MIN(T a, T b)
{
  return (a < b) ? a : b;
}

template <typename T>
CircularArray<T>::CircularArray()
{
  minimumValue = 0;
  maximumValue = 255;
  currentIndex = 0;
  usedIndexes = 0;
}

template <typename T>
CircularArray<T>::CircularArray(T minValue, T maxValue) : CircularArray()
{
  minimumValue = minValue;
  maximumValue = maxValue;
}

template <typename T>
T CircularArray<T>::getAverage()
{
  if (usedIndexes == 0) return 0;
  unsigned int avg = 0;
  for (unsigned char i = 0; i < usedIndexes; ++i)
  {
    avg += (unsigned int)values[i];
  }
  /*Serial.print("avg sum: ");
  Serial.println(avg);
  Serial.print("usedIndexes: ");
  Serial.println(usedIndexes);*/
  avg /= usedIndexes;
  
  return (T)avg;
}

template <typename T>
void CircularArray<T>::addValue(T value)
{
  if (value > minimumValue && value <= maximumValue)
  {
    values[currentIndex] = value;
    if (usedIndexes < TOTAL_VALUES) ++usedIndexes;
    currentIndex = (++currentIndex) % usedIndexes;
  }
}

template <typename T>
void CircularArray<T>::dumpArray()
{
  for (unsigned char i = 0; i < usedIndexes; ++i)
  {
    Serial.print("i");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(values[i]);
  }
}

