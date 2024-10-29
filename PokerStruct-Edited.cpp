#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <array>
#include <algorithm>

/// @brief The Card Suit, use to define the suit of a poker card.
enum class CardSuit {
    /// @brief Invalid Card Suit value, do not use.
    Invalid = 0,

    Hearts = 1,
    Diamonds = 2,
    Spades = 3,
    Clubs = 4
};

/// @brief The Card Rank, use to define the rank of a poker card.
enum class CardRank {
    /// @brief Invalid card rank value, do not use.
    Invalid = 0,

    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 11,
    Queen = 12,
    King = 13,
    Ace = 14
};

/// @brief The Card struct, represent a poker card.
struct Card {
public:
    /// @brief The suit of the card. Default to Invalid.
    CardSuit Suit = CardSuit::Invalid;
    /// @brief The rank of the card. Default to Invalid.
    CardRank Rank = CardRank::Invalid;

    /// @brief Create a new empty (invalid) Cards.
    Card() = default;
    /// @brief Create a new Card.
    /// @param rank The rank of the card.
    /// @param suit The suit of the card.
    Card(CardRank rank, CardSuit suit) : Suit(suit), Rank(rank) {}
};

/// @brief The Hand Rank, use to define the rank of the player hand.
enum class HandRank {
    StraightFlush = 9, Quad = 8, FullHouse = 7, Flush = 6, 
    Straight = 5, Set = 4, TwoPair = 3, Pair = 2, HighCard = 1
};

/// @brief The Deck struct, represent the deck of a poker game (52 cards).
struct Deck {
private:
    std::vector<Card> deck;
public:
    Deck() : deck(52) {
        // Init card.
        int i = 0;
        for (int suit = 1; suit <= 4; suit++)
            for (int rank = 1; rank <= 13; rank++, i++)
                deck[i] = Card((CardRank)rank, (CardSuit)suit);
        
        // Shuffle card.
        Shuffle();
    }

    /// @brief Shuffle the current deck (the deck will automatically shuffled when creating).
    void Shuffle() {
        std::srand(std::time(nullptr));
        std::random_shuffle(deck.begin(), deck.end());
    }

    /// @brief Draw the top card from the deck (if there's at least a card in the deck).
    /// @return The top card from the deck, or an invalid card if the deck is empty.
    Card DrawCard() {
        if (deck.empty()) {
            std::cout << "Hết bài rồi";
            return Card();
        }

        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }

    /// @brief Check if the Deck is empty.
    /// @return true if the Deck is empty, false otherwise.
    bool IsEmpty() const { return deck.empty(); }
};

/// @brief Get the name of the given card rank.
/// @param rank The rank of the card to get.
/// @return The name of the given card rank.
const char* GetCardRankName(CardRank rank) {
    switch (rank) {
        case CardRank::Two:
            return "Two";
        case CardRank::Three:
            return "Three";
        case CardRank::Four:
            return "Four";
        case CardRank::Five:
            return "Five";
        case CardRank::Six:
            return "Six";
        case CardRank::Seven:
            return "Seven";
        case CardRank::Eight:
            return "Eight";
        case CardRank::Nine:
            return "Nine";
        case CardRank::Ten:
            return "Ten";
        case CardRank::Jack:
            return "Jack";
        case CardRank::Queen:
            return "Queen";
        case CardRank::King:
            return "King";
        case CardRank::Ace:
            return "Ace";
        default:
            return "Unknown";
    }
}

/// @brief Get the name of the given card suit.
/// @param suit The suit of the card to get.
/// @return The name of the given card suit.
const char* CardSuitToString(CardSuit suit) {
    switch (suit) {
        case CardSuit::Hearts:
            return "Hearts";
        case CardSuit::Diamonds:
            return "Diamond";
        case CardSuit::Spades:
            return "Spades";
        case CardSuit::Clubs:
            return "Clubs";
        default:
            return "Unknown";
    }
}

/// @brief The Hand struct, represent the hand of the player.
struct Hand {
public:
    /// @brief The current card in the player hand.
    std::vector<Card> Cards;
    /// @brief The current rank of the player hand.
    HandRank Rank;

    /// @brief Sort the cards of the player hand.
    void SortHand() { 
        for (int i = 1; i < Cards.size(); ++i) {
            Card key = Cards[i];

            int j = i - 1;
            while (j >= 0 && static_cast<int>(Cards[j].Rank) > static_cast<int>(key.Rank)) {
                Cards[j + 1] = Cards[j];
                --j;
            }
            Cards[j + 1] = key;
        }
    }

    /// @brief Print the player hand.
    void PrintHand() {
        for (const auto& card : Cards) {
            std::cout << "Card: Rank " << GetCardRankName(card.Rank) 
                    << ", Suit " << CardSuitToString(card.Suit) << std::endl;
        }
    }


    /// @brief Check if the player hand is a pair.
    /// @return true if the player hand is a pair, false otherwise.
    bool IsPair() const {
        int pairCount = 0;
        for (int i = 0; i < 4; ++i) {
            if (Cards[i].Rank == Cards[i + 1].Rank) {
                ++pairCount;
                // ++i;  // Bỏ qua quân bài tiếp theo
                // if (i < 3 && cards[i].Rank == cards[i + 1].Rank) {
                //     return false;  // Tứ quý hoặc bộ ba, không phải một đôi
                // }
            }
        }
        return pairCount == 1;
    }

    /// @brief Check if the player hand is a set.
    /// @return true if the player hand is a set, false otherwise.
    bool IsSet() const {
        int count = 0;
        for (int i = 0; i < 3; ++i) {
            if (Cards[i].Rank == Cards[i + 1].Rank &&
                Cards[i + 1].Rank == Cards[i + 2].Rank) {
                ++count;
            }
        }
        return count == 1;
    }

    /// @brief Check if the player hand is two pair.
    /// @return true if the player hand is two pair, false otherwise.
    bool IsTwoPair() const {
        int count = 0;  // Đếm số cặp
        for (int i = 0; i < 4; ++i) {
            // Kiểm tra nếu quân bài hiện tại bằng quân bài tiếp theo
            if (Cards[i].Rank == Cards[i + 1].Rank) {
                ++count;  // Tăng số cặp
                ++i;      // Bỏ qua quân bài tiếp theo
            }
        }
        return count == 2;  // Trả về true nếu có 2 cặp
    }


    /// @brief Check if the player hand is straight.
    /// @return true if the player hand is straight, false otherwise.
    bool IsStraight() const {
        for (int i = 0; i < 4; ++i) {
            if (static_cast<int>(Cards[i].Rank) + 1 != static_cast<int>(Cards[i + 1].Rank)) {
                return false;
            }
        }
        return true;
    }

    /// @brief Check if the player hand is a flush.
    /// @return true if the player hand is a flush, false otherwise.
    bool IsFlush() const {
        for (int i = 0; i < 4; ++i) {
            if (Cards[i].Suit != Cards[i + 1].Suit) {
                return false;
            }
        }
        return true;
    }

    /// @brief Check if the player hand is full house.
    /// @return true if the player hand is full house, false otherwise.
    bool IsFullHouse() const { return IsSet() && IsTwoPair(); }

    /// @brief Check if the player hand is a quad.
    /// @return true if the player hand is a quad, false otherwise.
    bool IsQuad() const {
        // Kiểm tra tứ quý
        return (Cards[0].Rank == Cards[3].Rank) || 
            (Cards[1].Rank == Cards[4].Rank);
    }

    /// @brief Check if the player hand is straight flush.
    /// @return true if the player hand is straight flush, false otherwise.
    bool IsStraightFlush() const { return IsStraight() && IsFlush(); }


// double EvaluateHand() {
//     if (IsStraightFlush()) {
//         return 9 * 14 +static_cast<int>(cards[4].Rank);
//     }
//     else if (IsQuad()) {
//         return 8 * 14 + static_cast<int>(cards[3].Rank);  // cards[3], cards[2] will be a quad
//     }
//     else if (IsFullHouse()) {
//         return 7 * 14 + static_cast<int>(cards[3].Rank);
//     }
//     else if (IsFlush()) {
//         return 6 * 14 + static_cast<int>(cards[4].Rank);  // Danh gia them
//     }
//     else if (IsStraight()) {
//         return 5 * 14 +static_cast<int>(cards[4].Rank);
//     }
//     else if (IsSet()) {
//         return 4 * 14 + static_cast<int>(cards[3].Rank);
//     }
//     else if (IsTwoPair()) {
//         return HandRank::TwoPair;
//     }
//     else if (IsPair()) {
//         return HandRank::Pair;
//     }
//     else {
//         return HandRank::HighCard; // Nếu không thuộc loại nào khác, sẽ là "High Card"
//     }
// }

double EvaluateHand() {
    if (IsStraightFlush()) {
        return 9 * pow(14, 5) + static_cast<int>(Cards[4].Rank) * pow(14, 4) +
               static_cast<int>(Cards[3].Rank) * pow(14, 3) +
               static_cast<int>(Cards[2].Rank) * pow(14, 2) +
               static_cast<int>(Cards[1].Rank) * pow(14, 1) +
               static_cast<int>(Cards[0].Rank);
    }
    else if (IsQuad()) {
        return 8 * pow(14, 5) + static_cast<int>(Cards[3].Rank) * pow(14, 4) +
               static_cast<int>(Cards[4].Rank); // Lá bài thứ 5 có thể là kicker
    } 
    else if (IsFullHouse()) {
        return 7 * pow(14, 5) + static_cast<int>(Cards[2].Rank) * pow(14, 4) +
       -        static_cast<int>(Cards[4].Rank); // Bộ ba và đôi
    }
    else if (IsFlush()) {
        return 6 * pow(14, 5) + static_cast<int>(Cards[4].Rank) * pow(14, 4) +
               static_cast<int>(Cards[3].Rank) * pow(14, 3) +
               static_cast<int>(Cards[2].Rank) * pow(14, 2) +
               static_cast<int>(Cards[1].Rank) * pow(14, 1) +
               static_cast<int>(Cards[0].Rank);
    }
    else if (IsStraight()) {
        return 5 * pow(14, 5) + static_cast<int>(Cards[4].Rank);
    }
    else if (IsSet()) {
        return 4 * pow(14, 5) + static_cast<int>(Cards[2].Rank) * pow(14, 4) +
               static_cast<int>(Cards[4].Rank); // Bộ ba và kicker cao
    } 
    else if (IsTwoPair()) {
        if (Cards[0].Rank != Cards[1].Rank) {
            return 3 * pow(14, 5) + static_cast<int>(Cards[4].Rank) * pow(14, 4) 
            + static_cast<int>(Cards[2].Rank) * pow(14, 3) 
            + static_cast<int>(Cards[1].Rank);
        } 
        else if (Cards[1].Rank != Cards[2].Rank){
            return 3 * pow(14, 5) + static_cast<int>(Cards[4].Rank) * pow(14, 4) 
            + static_cast<int>(Cards[1].Rank) * pow(14, 3) 
            + static_cast<int>(Cards[2].Rank);
        } else {
            return 3 * pow(14, 5) + static_cast<int>(Cards[3].Rank) * pow(14, 4) 
            + static_cast<int>(Cards[1].Rank) * pow(14, 3) 
            + static_cast<int>(Cards[4].Rank);
        }
    // Pair (too much calculation).
    }
    else if (IsPair()) { 
        if (Cards[0].Rank == Cards[1].Rank){
            return 2 * pow(14, 5) + static_cast<int>(Cards[0].Rank) * pow(14, 4)
            + static_cast<int>(Cards[4].Rank) * pow(14, 3)
            + static_cast<int>(Cards[3].Rank) * pow(14, 2)
            + static_cast<int>(Cards[2].Rank) * pow(14, 1);
        }
        else if (Cards[1].Rank == Cards[2].Rank){
            return 2 * pow(14, 5) + static_cast<int>(Cards[1].Rank) * pow(14, 4)
            + static_cast<int>(Cards[4].Rank) * pow(14, 3)
            + static_cast<int>(Cards[3].Rank) * pow(14, 2)
            + static_cast<int>(Cards[0].Rank) * pow(14, 1);
        }
        else if (Cards[2].Rank == Cards[3].Rank){
            return 2 * pow(14, 5) + static_cast<int>(Cards[3].Rank) * pow(14, 4)
            + static_cast<int>(Cards[4].Rank) * pow(14, 3)
            + static_cast<int>(Cards[1].Rank) * pow(14, 2)
            + static_cast<int>(Cards[0].Rank) * pow(14, 1);
        }
        else {
            return 2 * pow(14, 5) + static_cast<int>(Cards[3].Rank) * pow(14, 4)
            + static_cast<int>(Cards[2].Rank) * pow(14, 3)
            + static_cast<int>(Cards[1].Rank) * pow(14, 2)
            + static_cast<int>(Cards[0].Rank) * pow(14, 1);
        }
    }
    else {
        // High Card
        return 1 * pow(14, 5) + static_cast<int>(Cards[4].Rank) * pow(14, 4) +
               static_cast<int>(Cards[3].Rank) * pow(14, 3) +
               static_cast<int>(Cards[2].Rank) * pow(14, 2) +
               static_cast<int>(Cards[1].Rank) * pow(14, 1) +
               static_cast<int>(Cards[0].Rank);
    }
}
};



int main() {
    Hand hand, hand1;
    hand.Cards = {
        Card(CardRank::Ace, CardSuit::Hearts),
        Card(CardRank::King, CardSuit::Diamonds),
        Card(CardRank::Queen, CardSuit::Spades),  
        Card(CardRank::Jack, CardSuit::Clubs),
        Card(CardRank::Ten, CardSuit::Hearts)
    };
    hand1.Cards = {
        Card(CardRank::King, CardSuit::Hearts),
        Card(CardRank::King, CardSuit::Diamonds),
        Card(CardRank::King, CardSuit::Spades),  
        Card(CardRank::Ten, CardSuit::Clubs),
        Card(CardRank::Ten, CardSuit::Hearts)
    };

    Deck deck;

    for (int i = 0; i < 5; i++) {
        hand.Cards[i] = deck.DrawCard();
    }

    std::cout << "Hand before sorting:" << std::endl;
    hand.PrintHand();
    std::cout << "-------------------" << std::endl;
    hand1.PrintHand();

    hand.SortHand();
    hand1.SortHand();

    std::cout << "Player 1 "<< std::endl;
    hand.PrintHand();
    std::cout << "Hand evaluation:" << std::endl;
    std::cout << "Pair: " << hand.IsPair() << std::endl;
    std::cout << "Set: " << hand.IsSet() << std::endl;
    std::cout << "Two Pair: " << hand.IsTwoPair() << std::endl;
    std::cout << "Straight: " << hand.IsStraight() << std::endl;
    std::cout << "Flush: " << hand.IsFlush() << std::endl;
    std::cout << "Full House: " << hand.IsFullHouse() << std::endl;
    std::cout << "Quad: " << hand.IsQuad() << std::endl;
    std::cout << "Straight Flush: " << hand.IsStraightFlush() << std::endl;

    std::cout << "\n\nPlayer 2:" << std::endl;
    hand1.PrintHand();
    std::cout << "Hand evaluation:" << std::endl;
    std::cout << "Pair: " << hand1.IsPair() << std::endl;
    std::cout << "Set: " << hand1.IsSet() << std::endl;
    std::cout << "Two Pair: " << hand1.IsTwoPair() << std::endl;
    std::cout << "Straight: " << hand1.IsStraight() << std::endl;
    std::cout << "Flush: " << hand1.IsFlush() << std::endl;
    std::cout << "Full House: " << hand1.IsFullHouse() << std::endl;
    std::cout << "Quad: " << hand1.IsQuad() << std::endl;
    std::cout << "Straight Flush: " << hand1.IsStraightFlush() << std::endl;

    double score1 = hand.EvaluateHand(), score2 = hand1.EvaluateHand();
    if (score1 < score2)
        std::cout << "Player 2 win";
    else if (score1 > score2)
        std::cout << "Player 1 win";
    else
        std::cout << "Tie";

    return 0;
}
