#include <iostream>
#include <string>
#include <array>
#include <vector>


#include<QCoreApplication>
using namespace std;


class JobRecord
{
protected:
    int mStartYear;
    int mEndYear;
    std::string mJobTitle;
    std::string mCompanyName;
public:
    JobRecord():
        mStartYear(0),mEndYear(0), mJobTitle(""), mCompanyName("")
    {

    }
    JobRecord(int a, int b, std::string c,std:: string d) :
        mStartYear(a), mEndYear(b), mJobTitle(c), mCompanyName(d)
    {

    }
bool isValid() const
{  return((mStartYear>1960)&&(mEndYear>1960))
            && (mCompanyName.length()>1)
            && (mJobTitle=="developer" || mJobTitle=="junior developer" || mJobTitle=="senior software developer");
}

void print() const
   {
           std::cout<<mStartYear<<"-"<<mEndYear<<" worked as "<<mJobTitle<<" in "<<mCompanyName<<std::endl;
   }
int calc()
{
   return mEndYear-mStartYear;
}
};



class CV
{
public:
    CV( const std::string &name, int birthYear, const std::string &skills, const std::list <JobRecord>&previousJobs) :
        mName{name}
      , mBirthYear{birthYear}
      , mSkills{skills}
      , mPreviousJobs{previousJobs}
    {

    }
    CV( const  std::string &name, int birthYear, const std::string &skills) :
           mName{name}
         , mBirthYear{birthYear}
         , mSkills{skills}
       {

       }

    bool isValid() const
    {    for(auto elem: mPreviousJobs)
        {
            if(!elem.isValid())
            {
               return false;
            }
        }
        return !mName.empty()
                && ((mBirthYear > 1970) && (mBirthYear < 1995))
                && !mSkills.empty()
                && !mPreviousJobs.empty();
    }

    void print() const
    {
        if (isValid())
        {
            std::cout << mName << " "<< mBirthYear << std::endl;
            std::cout << "\n" << std::endl;
            std::cout << "Skills: " << mSkills << std::endl;
            std::cout << "Previous Jobs: "  << std::endl;
            for_each(mPreviousJobs.begin(),mPreviousJobs.end(),[](JobRecord a){a.print();});
            std::cout << std::endl;
        }
    }
        void addJobRecord(JobRecord&toAdd)
        {
           mPreviousJobs.push_back(toAdd);
        }
        int find()

        {
            int sum=0;
                   for(auto elem: mPreviousJobs)
                   {
                       sum+=elem.calc();
                   }
                   return sum;

        }


private:
    std::string mName;
    int mBirthYear;
    std::string mSkills;
    std::list <JobRecord> mPreviousJobs;
};





int main()
{

    CV johnsCV {"John Jonson", 1978,"C++, Java"};
    JobRecord johnsRec1{1990,1995,"developer","IBM"};
    JobRecord johnsRec2{1996,2002,"senior software developer","Microsoft"};

    johnsCV.addJobRecord((johnsRec1));
    johnsCV.addJobRecord((johnsRec2));

    CV dansCV("Dan Davidson", 1988, "C++, Java");
    JobRecord dansRec{1996,1997,"developer","IBM"};
    dansCV.addJobRecord(dansRec);

    CV bensCV("Ben  Clarkson", 1977, "C++, Python");
    JobRecord bensRec1{1993,1997,"senior software developer","SoftServe"};
    JobRecord bensRec2{1997,2000,"developer","NASA"};
    JobRecord bensRec3{2001,2008,"developer","IBM"};
    JobRecord bensRec4{2008,2014,"junior developer","Google"};
    bensCV.addJobRecord(bensRec1);
    bensCV.addJobRecord(bensRec2);
    bensCV.addJobRecord(bensRec3);


    std::vector<CV> cvList;
    cvList.push_back(johnsCV);
    cvList.push_back(dansCV);
    cvList.push_back(bensCV);


    for (const auto& cv: cvList)
    {
            cv.print();
    }

    std::cout<<"Worked more than 5 years:"<<std::endl;
    for (auto cv: cvList)
    {
        if ((cv.find())>=5 )
        {
            cv.print();
        }
    }


    return 0;
}


