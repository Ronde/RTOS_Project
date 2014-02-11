#ifndef  SLICE-AND-PLAY_H
#define  SLICE-AND-PLAY_H

class ring {

public:
	
	//return an instance of ring;
	static ring&  instance();
	
	/**it will ring in word the number of step passed by parameter, 
	*\it'll include "Hai fatto" - number of step in word - "passi"
	* second int parameter is used for the volume (from 0 to 100)
	*/
	void play_n_of_step(int,int);

	//ring the song of the defeat, int parameter is used for the volume (from 0 to 100)
	void looser_Song(int);
	
	//ring the song of victory, int parameter is used for the volume (from 0 to 100)
	void victory_Song(int);
	
private:
	
	//ring the numbers between 10 and 19 
	void say_tens_and_unit(int);
	
	//ring the tens between 20 and 90
	void say_tens (int);
	
	//ring the numbers between 1 and 9
	void say_unit (int);


	
	void addItemToVector( const unsigned char *,const unsigned int);
	void  numb_impl();



};
#endif
