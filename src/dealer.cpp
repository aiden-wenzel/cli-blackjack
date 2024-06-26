#include "../include/cli_blackjack/card.hpp"
#include "../include/cli_blackjack/deck.hpp"
#include "../include/cli_blackjack/player.hpp"
#include "../include/cli_blackjack/dealer.hpp"


Dealer::Dealer() {
    this->hand = {};
    this->card_sum = 0;
}

void Dealer::deal(Player* player, Deck* deck) {
    Card deal_card = deck->remove_top_card();
    int card_value = deal_card.get_value();
    player->card_sum += card_value;
    player->add_card(deal_card);
    deck->num_cards--;
}

void Dealer::deal(Dealer* dealer, Deck* deck) {
    Card deal_card = deck->remove_top_card();
    int card_value = deal_card.get_value();
    dealer->card_sum += card_value;
    dealer->add_card(deal_card);
    deck->num_cards--;
}

void Dealer::add_card(const Card& card) {
    this->hand.push_back(card);
}
int Dealer::get_card_sum() {
    return this->card_sum;
}

int Dealer::get_hand_size() {
    return this->hand.size();
}

void Dealer::print_hand(std::ostream& output) {
    output << "Dealers hand: [";
    for (size_t i = 0; i < this->hand.size(); i++) {
        if (i == this->hand.size()-1) {
            output << this->hand[i];
            break;
        }
        output << this->hand[i] << " | ";
    }
    output << "]\n";
}

bool Dealer::hit(int player_card_sum) {
   if (this->card_sum < player_card_sum) {
       return true;
   } 
   return false;
}

void Dealer::clear_hand() {
    this->hand.erase(this->hand.begin(), this->hand.end());
    this->card_sum = 0;
}
