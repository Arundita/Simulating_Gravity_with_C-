
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<sstream>

using namespace std;
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
using namespace sf;

int main(int, char const**)
{
    system("pwd");
    //create a video mode object
    VideoMode vm(800,600);
    //system("pwd");
    //Create and open a window for the game
    RenderWindow window(vm,"Game !!!",Style::Fullscreen);
    
    Texture asteroid;
    asteroid.loadFromFile("graphics/asteroid.png");
    Sprite spriteAsteroid;
    spriteAsteroid.setTexture(asteroid);
    spriteAsteroid.setPosition(1500, 600);
    spriteAsteroid.setScale(2, 2);
    spriteAsteroid.setRotation(180.f);
    
    const float gravity = 0.5;  //define gravity
    int groundHeight = 1500;           //we need a height for the grounf=d usrface where the object would fall
    float moveSpeed = 7.0;             //to movethe object left or right
    float jumpSpeed = 35.0f;             // to make the object jump in y or -y direction;
    Vector2f velocity(Vector2f(0,0));          //define velocity for the objects

    Texture textureBg;
    textureBg.loadFromFile("graphics/d.png");
    Vector2u textureSize;  //Added to store texture size.
    textureSize = textureBg.getSize();
    Vector2u windowSize;   //Added to store window size
    windowSize = window.getSize();
    Sprite spriteBg;
    spriteBg.setTexture(textureBg);
    float ScaleX = (float) windowSize.x / textureSize.x;
    float ScaleY = (float) windowSize.y / textureSize.y;     //Calculate scale.
    spriteBg.setScale(ScaleX, ScaleY);
    
    Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
                 window.close();
             }
            
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Right){
                velocity.x = moveSpeed;
                velocity.y = -jumpSpeed;
                
                if(spriteAsteroid.getPosition().x > 2800){
                    spriteAsteroid.setPosition(30, 1500);
                }
            }
            else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Left){
                velocity.x = -moveSpeed;
                velocity.y = -jumpSpeed;
                
                if(spriteAsteroid.getPosition().x < 70){
                    spriteAsteroid.setPosition(2800, 1500);
                }
            }
            else{
                velocity.x = 0;
            }
            
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Up){
                velocity.y = -jumpSpeed;
            }
         }
    
        if(spriteAsteroid.getPosition().y < groundHeight || velocity.y < 0){  //in the air i.e. above the ground
            //then activate gravity
            velocity.y += gravity;
        }
        else{
            spriteAsteroid.setPosition(spriteAsteroid.getPosition().x,groundHeight); // reset the object on the ground if
            velocity.y = 0;
        }
        spriteAsteroid.move(velocity.x,velocity.y);
       // spriteAsteroid.rotate(.5f);
        
        window.clear();
        window.draw(spriteBg);//close previos frame of animation
        window.draw(spriteAsteroid);
        window.display();   //show everything we just drew
    }
    
    return EXIT_SUCCESS;
    }
    
