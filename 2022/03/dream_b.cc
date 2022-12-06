int solB(lines)
{
  assert(*lines.rbegin()!="");
  
  auto b = badges(lines);

  //Number of badges should be a third of the number of rucksacks
  assert(3*b.size() == lines.size());

  return sumUp(b);
}

string badges(lines)
{
  string ret;
  ret.reserve(lines.size());
  
  ret = iterateEveryCombination( lines, badge(a,b,c));

}

string iterateEveryCombination(lines)

optional<char>
badge(&a,&b,&c)
{
  auto common = inAll(a,b,c);
  if(common)
    return {common.first()};
  else
    return {};
}
