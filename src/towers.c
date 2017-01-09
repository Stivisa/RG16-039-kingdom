#include "kingdom_main.h"

//Osnovne funckije za pravljenje kula koje ce se koristiti u igrici


//Osnovna kula
void basicTower(tower t)
{
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);
    currentTexture = textures[t.texture];

    //osnova kule
    cylinder(0, 0, 0, 1, 3);
    //srednji deo
    cylinder(0, 3, 0, 1.5, 1);
    //Centar
    cylinder(0, 4, 0, 1.2, 1);

    currentTexture = textures[TEX_DEFAULT];

    //velicina oblasti koju kula moze da napada
    if (t.range > -1 && showAttackRadius) {
	  circle(t.range);
    }

    glPopMatrix();
}

//napredna kula
//Sastoji se od osnovne kule plus bodlje
void advancedTower(tower t)
{
    tower t2 = { 0, OBJ_BASIC, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, t.texture, {1, 1, 1},
				t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
	};
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);
    basicTower(t2);

    //siljci
    spike(0, 1.2, -3, 0.5, 1, DEF_D, 90, 0, 0);
    spike(0, 1.2, 3, 0.5, 1, DEF_D, -90, 0, 0);
    spike(3, 1.2, 0, 0.5, 1, DEF_D, 0, 0, 90);
    spike(-3, 1.2, 0, 0.5, 1, DEF_D, 0, 0, -90);


    spike(0, 1.2, -3, 0.5, 1, DEF_D, 90, 45, 0);
    spike(0, 1.2, 3, 0.5, 1, DEF_D, -90, 45, 0);
    spike(0, 1.2, -3, 0.5, 1, DEF_D, 90, -45, 0);
    spike(0, 1.2, 3, 0.5, 1, DEF_D, -90, -45, 0);

    glPopMatrix();
}

//kupasta kula
void coneTower(tower t)
{
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);
    currentTexture = textures[t.texture];

    //osnova
    cone(0, -3, 0, 1.4, 4, DEF_D);
    //srednji deo
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    cone(0, -3, 0, 1.4, 4, DEF_D);
    glPopMatrix();
    //vrh
    cylinder(0, 4.0, 0, 1.5, 1.0);

    currentTexture = textures[TEX_DEFAULT];

    //Oblast napada
    if(t.range > -1 && showAttackRadius){
	  circle(t.range);
    }
    glPopMatrix();
}

//napredna kupasta kula kao obicta samo sa siljkovima
void advancedConeTower(tower t)
{
    tower t2 ={ 0, OBJ_CONE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, t.texture, {1, 1, 1},
			  t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
	};
    
	glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);
    coneTower(t2);

    //siljkovi
    spike(0, 1.2, -4, 0.5, 1, DEF_D, 90, 0, 0);
    spike(0, 1.2, 4, 0.5, 1, DEF_D, -90, 0, 0);
    spike(4, 1.2, 0, 0.5, 1, DEF_D, 0, 0, 90);
    spike(-4, 1.2, 0, 0.5, 1, DEF_D, 0, 0, -90);

    spike(0, 1.2, -4, 0.5, 1, DEF_D, 90, 45, 0);
    spike(0, 1.2, 4, 0.5, 1, DEF_D, -90, 45, 0);
    spike(0, 1.2, -4, 0.5, 1, DEF_D, 90, -45, 0);
    spike(0, 1.2, 4, 0.5, 1, DEF_D, -90, -45, 0);

    glPopMatrix();
}

//kockasta kula
void squareTower(tower t)
{
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);
    currentTexture = textures[t.texture];

    //osnova
    cylinder(0, 0, 0, 1, 3);
    //srednji deo
    cube(0, 3.5, 0, 1.5, .5, 1.5, 0);
    //piramida
    pyramid(0, 4, 0, 0.75, 0.75, 0.75, 0);

    currentTexture = textures[TEX_DEFAULT];

    //Oblast napada
    if (t.range > -1 && showAttackRadius) {
	  circle(t.range);
    }
    glPopMatrix();
}

//naprdna kockasta kula, kockasta kula sa siljkovima
void advancedSquareTower(tower t)
{
    tower t2 ={ 0, OBJ_SQUARE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, t.texture, {1, 1, 1},
			  t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
    
	glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);
    
	//osnova
    squareTower(t2);

    //silkovi
    spike(0, 1.2, -3.5, 0.5, 1, DEF_D, 90, 0, 0);
    spike(0, 1.2, 3.5, 0.5, 1, DEF_D, -90, 0, 0);
    spike(3.5, 1.2, 0, 0.5, 1, DEF_D, 0, 0, 90);
    spike(-3.5, 1.2, 0, 0.5, 1, DEF_D, 0, 0, -90);


    spike(0, 1.6, -3.5, 0.5, 1, DEF_D, 90, 45, 0);
    spike(0, 1.6, 3.5, 0.5, 1, DEF_D, -90, 45, 0);
    spike(0, 1.6, -3.5, 0.5, 1, DEF_D, 90, -45, 0);
    spike(0, 1.6, 3.5, 0.5, 1, DEF_D, -90, -45, 0);

    glPopMatrix();
}

//vatrena kula, obicna kula sa sferom iznad kule
void fireTower(tower t)
{
    tower t2 ={ 0, OBJ_FIRE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_FIRE, {1, 1, 1},
				t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);

    basicTower(t2);
    
	currentTexture = textures[TEX_FIRE];
    sphere(0, 6.2, 0, 1, towerTh);
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}

//napredna vatrena kula, vatrena kula sa siljkovima
void advanceFireTower(tower t)
{
    tower t2 ={ 0, OBJ_FIRE2, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_FIRE, {1, 1, 1},
			  t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);

    advancedTower(t2);
    
	currentTexture = textures[TEX_FIRE];
    sphere(0, 6.2, 0, 1, towerTh);
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}

//ledena kula, obicna kula sa zvezdom iznad
void iceTower(tower t)
{
    tower t2 ={ 0, OBJ_ICE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_ICE, {1, 1, 1},
				t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
	
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);

    basicTower(t2);
    
	currentTexture = textures[TEX_ICE];
    star(0, 6.2, 0, 0.25, 0.25, 0.25, towerTh);
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}

//napredna ledena kula, ledena kula sa siljkovima
void advanceIceTower(tower t)
{
    tower t2 ={ 0, OBJ_ICE2, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_ICE, {1, 1, 1},
			  t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
    
	glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);

    advancedTower(t2);
    
	currentTexture = textures[TEX_ICE];
    star(0, 6.2, 0, 0.25, 0.25, 0.25, towerTh);
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}

//zemljana kula, obicna kula sa sferom iznad
void earthTower(tower t)
{
    tower t2 ={ 0, OBJ_EARTH, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_EARTH, {1, 1, 1},
			  t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
	
    glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);

    coneTower(t2);
    
	currentTexture = textures[TEX_EARTH];
    sphere(0, 6.2, 0, 1, towerTh);
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}

//napredna zemljana kula, zemljana kula sa siljcima
void advanceEarthTower(tower t)
{
    tower t2 = { 0, OBJ_EARTH, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_EARTH, {1, 1, 1},
				t.name, 1, t.range, t.damage, t.fireRate, 0, t.cost, "Description"
    };
    
	glPushMatrix();
    glTranslated(t.translation.x, t.translation.y, t.translation.z);
    glRotated(t.rotation.y, 0, 1, 0);
    glScaled(t.scale.x, t.scale.y, t.scale.z);

    advancedConeTower(t2);
    currentTexture = textures[TEX_EARTH];
    sphere(0, 6.2, 0, 1, towerTh);
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}
