/*
Your task in order to complete this Kata is to write a function which formats a duration, given as a number of seconds, in a human-friendly way.

The function must accept a non-negative integer. If it is zero, it just returns "now". Otherwise, the duration is expressed as a combination of years, days, hours, minutes and seconds.

It is much easier to understand with an example:

format_duration(62)    // returns "1 minute and 2 seconds"
format_duration(3662)  // returns "1 hour, 1 minute and 2 seconds"
For the purpose of this Kata, a year is 365 days and a day is 24 hours.

Note that spaces are important.

Detailed rules
The resulting expression is made of components like 4 seconds, 1 year, etc. In general, a positive integer and one of the valid units of time, separated by a space. The unit of time is used in plural if the integer is greater than 1.

The components are separated by a comma and a space (", "). Except the last component, which is separated by " and ", just like it would be written in English.

A more significant units of time will occur before than a least significant one. Therefore, 1 second and 1 year is not correct, but 1 year and 1 second is.

Different components have different unit of times. So there is not repeated units like in 5 seconds and 1 second.

A component will not appear at all if its value happens to be zero. Hence, 1 minute and 0 seconds is not valid, but it should be just 1 minute.

A unit of time must be used "as much as possible". It means that the function should not return 61 seconds, but 1 minute and 1 second instead. Formally, the duration specified by of a component must not be greater than any valid more significant unit of time.
*/

struct part {
  char unit;
  int amount;
  part(char u, int a) {
    unit = u;
    amount = a;
  }
};

std::string getUnit(char c, bool singular) {
  std::string out;
  switch (c)
  {
  case 's':
    out = "second";
    break;
  case 'm':
    out = "minute";
    break;
  case 'h':
    out = "hour";
    break;
  case 'd':
    out = "day";
    break;
  case 'y':
    out = "year";
    break;
  }
  if (!singular) out += "s";
  return out;
}

std::string format_duration(int seconds)
{
  std::string out = "";
  std::vector<part> p{};

  if (!seconds) return "now";

  int s = seconds % 60;
  if (s) p.push_back(part('s', s));

  int m = seconds / 60 % 60;
  if (m) p.push_back(part('m', m));

  int h = seconds / 3600 % 24;
  if (h) p.push_back(part('h', h));

  int d = seconds / 86400 % 365;
  if (d) p.push_back(part('d', d));

  int y = seconds / 31536000;
  if (y) p.push_back(part('y', y));

  for (int i = p.size() - 1; i >= 0; --i) {
    if (p.size() - 1 == i) out += std::to_string(p.back().amount) + " " + getUnit(p.back().unit, 1 == p.back().amount);
    else if (i < p.size() - 1 && i == 0) out += " and " + std::to_string(p[i].amount) + " " + getUnit(p[i].unit, 1 == p[i].amount);
    else out += ", " + std::to_string(p[i].amount) + " " + getUnit(p[i].unit, 1 == p[i].amount);
  }
  return out;
}
