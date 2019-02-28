/*
 * LectureAudio.h
 *
 *  Created on: 4 févr. 2019
 *      Author: jgaud
 */

#ifndef SOURCE_C_LECTUREAUDIO_H_
#define SOURCE_C_LECTUREAUDIO_H_

//fonction appelée par l'AIC à son sample rate
interrupt void audio(void) {


    if(playback_en_cours == 0) //Renvoie rien si la lecture n'est pas demandée
        output_sample(0);

    //Lecture de l'enregistrement si on a demandé la lecture et si on a pas dépassé le temps maximum de lecture
    if(playback_en_cours == 1 && playback_timer < PLAYBACK_TIMER_MAX){
        output_sample((buffer[i]-512) * gain); //On recentre le signal sur 0 et on le multiplie par le gain
        i++;
        playback_timer++;
    }

    //Si le temps de lecture est dépassé on arrête la lecture
    if(playback_timer >= PLAYBACK_TIMER_MAX){
        playback_en_cours = 0;
    }


    return;
}



#endif /* SOURCE_C_LECTUREAUDIO_H_ */
