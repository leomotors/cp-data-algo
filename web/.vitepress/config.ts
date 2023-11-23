import { defineConfig } from "vitepress";

import graderItems from "./grader.g";
import quizItems from "./quiz.g";
import algoItems from "./algo.g";

export default defineConfig({
  lang: "th",
  title: "Intro Data Struct",
  description: "Website containing my code for INTRO DATA STRUCT",
  lastUpdated: true,
  outDir: "../dist",

  head: [
    [
      "link",
      {
        rel: "stylesheet",
        href: "https://fonts.googleapis.com/css?family=IBM+Plex+Sans+Thai:r,i,b,bi",
      },
    ],
  ],

  themeConfig: {
    footer: {
      message: "Released under the MIT License",
      copyright: "Copyright © 2023 Nutthapat Pongtanyavichai",
    },
    socialLinks: [
      {
        icon: "github",
        link: "https://github.com/Leomotors/2110211-intro-data-struct",
      },
    ],

    sidebar: [
      {
        collapsed: false,
        text: "Introduction",
        items: [
          {
            text: "vtwi;t",
            link: "/introduction/",
          },
        ],
      },
      {
        collapsed: false,
        text: "My Grader Solutions",
        items: graderItems,
      },
      {
        collapsed: false,
        text: "My Quiz Solutions",
        items: quizItems,
      },
      {
        collapsed: false,
        text: "Algorithm Design",
        items: algoItems,
      },
    ],
  },
});
