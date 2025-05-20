#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


/* In this program I have multiple functions showing off 3 different debugging 
techniques, I feel that learning different methods to debug
is one of the most important things you can do as a programmer. Debugging
will always be a necessary skill in any programming related profession*/

/* -----------------------------------------------------------
  PRINT DEBUGGING
   -----------------------------------------------------------
   With print debugging we want to 
   show how sprinkling `std::cout` statements lets us
         watch data evolve and spot mistakes.
   Example bug: We want the sum of *positive* numbers only,
                but we wrote the loop wrong on purpose.
----------------------------------------------------------------*/
int sumPositive(const std::vector<int>& v)
{
    int sum = 0;
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        /* these print statements can help us understand
        where the program is messing up
         after testing, we remove once the bug is fixed */
        std::cout << "[print-debug] i=" << i
                  << "  v[i]=" << v[i]
                  << "  runningSum(before)=" << sum << '\n';

        /*   the bug is that it should be  if (v[i] > 0) …                     *
         *this is because negative numbers sneak into the sum.        */
        /* WRONG */  /* if (v[i] > 0) */ sum += v[i];

        std::cout << "[print-debug] runningSum(after)=" << sum << "\n\n";
    }
    return sum;
}

/* -----------------------------------------------------------
   RUBBER-DUCK DEBUGGING
   -----------------------------------------------------------
   This method of debugging is more to help programmers run through their line of code
   so that they can spot any mistakes they made. You pretend that you are talking
   to a rubber duck
----------------------------------------------------------------*/
bool isPalindrome(const std::string& s)
{
    // Hello, Duck!  🦆
    // I’m going to walk two pointers, one from the front (l)
    // and one from the back (r).  If at any point the letters
    // differ, the string is *not* a palindrome.

    std::size_t l = 0;                 // left pointer
    std::size_t r = s.size() - 1;      // right pointer

    while (l < r)                      // keep going while pointers haven’t crossed
    {
        if (s[l] != s[r])              // letters differ → fail
            return false;
        ++l;                           // move left needle forward
        --r;                           // move right needle backward
    }
    // Every mirrored pair matched, so the word reads the same
    // forwards and backwards.
    return true;
}

/* -----------------------------------------------------------
    WOLF-FENCE DEBUGGING
   -----------------------------------------------------------
   this involves repeatedly “fencing off” half the territory to isolate
         the wolf or the  bug.
   We intentionally broke multiplication (we used + instead of *).
   The helper shows how you could keep narrowing your search.
----------------------------------------------------------------*/
int buggyMultiply(int a, int b)        // <— The lone wolf lives here!
{
    return a + b;                      // BUG: should be a * b
}

int multiplyWithFences(int a, int b)
{
    // Fence #1: Confirm *inputs* are fine (they are).
    // Fence #2: Bypass everything *before* buggyMultiply – still wrong,
    //           so the wolf must be inside that function.
    return buggyMultiply(a, b);
}


void printDebuggingDemo()
{
    std::cout << "\n====== Print Debugging Demo ======\n";
    std::vector<int> data {3, -1, 2, 8, -5};
    int result = sumPositive(data);
    std::cout << "\n(Incorrect) sumPositive(...) returned "
              << result << "  ← watch the logs above to spot why.\n";
}

void rubberDuckDebuggingDemo()
{
    std::cout << "\n====== Rubber Duck Debugging Demo ======\n";
    std::string word = "racecar";
    std::cout << "Is \"" << word << "\" a palindrome?  "
              << std::boolalpha << isPalindrome(word) << "\n";
    std::cout << "(Open the source and read the comments aloud to your duck.)\n";
}

void wolfFenceDebuggingDemo()
{
    std::cout << "\n====== Wolf Fence Debugging Demo ======\n";
    int a = 7, b = 6;
    int product = multiplyWithFences(a, b);
    std::cout << a << " * " << b << " should be 42 but we got "
              << product << ".\n";
    std::cout << "We fenced off code until the wolf was traced to "
                 "`buggyMultiply()`.\n";
}

/* ============================================================*/
int main()
{
    printDebuggingDemo();
    rubberDuckDebuggingDemo();
    wolfFenceDebuggingDemo();
    return 0;
}
