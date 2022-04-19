package com.jesen.jnithreadinvoke.base;

import android.util.Log;

public class Question {
    private static final String TAG = "Question";
    protected String title;

    public static int score = 100;

    public Question(String title) {
        Log.d(TAG, "constructor Question ,title: " + title);
        this.title = title;
    }

    public String getTitle() {
        return this.title;
    }

    public static int getScore() {
        Log.d(TAG, "getScore");
        return score;
    }

    public void settingMaxScore(int score) {
        Log.d(TAG, "settingMaxScore, score: " + score);
    }
}
