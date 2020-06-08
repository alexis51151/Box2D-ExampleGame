class PlayerDowncomand : public Icommand
{
public:
	virtual void execute(Player* player) override {
		player->actionUp();
	}
private:

};

